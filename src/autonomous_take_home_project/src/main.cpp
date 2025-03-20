#include <cmath>
#include <chrono>
#include <algorithm>
#include <deque>

#include <rclcpp/rclcpp.hpp>
#include <msgs/msg/location_stamped.hpp>
#include <msgs/msg/response.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include "cubic_regression.hpp"

class LocationSubscriber : public rclcpp::Node
{
public:
    LocationSubscriber() : Node("location_subscriber")
    {
        sub = this->create_subscription<msgs::msg::LocationStamped>(
            "target_location", 10,
            std::bind(&LocationSubscriber::location_callback, this, std::placeholders::_1));

        pub = this->create_publisher<msgs::msg::Response>("response", 10);

        last_time = 0.0; // In seconds

        // This is the location of the simulated vehicle
        vehicle_last_location.x = 0.0;
        vehicle_last_location.y = 0.0;
        vehicle_last_location.z = 0.0;

        vehicle_last_velocity.x = 0.0;
        vehicle_last_velocity.y = 0.0;
        vehicle_last_velocity.z = 0.0;

        vehicle_last_angle = 0.0;

        target_last_location.x = 0.0;
        target_last_location.y = 0.0;
        target_last_location.z = 0.0;

        target_last_velocity.x = 0.0;
        target_last_velocity.y = 0.0;
        target_last_velocity.z = 0.0;

        target_last_angle = 0.0;

        lvtl = vehicle_last_location;

        max_history = 5;
        location_history.push_back({last_time, lvtl});
    }

private:
    void location_callback(const msgs::msg::LocationStamped::SharedPtr msg)
    {
        const double max_velocity = 10;
        const double max_acceleration = 2.5;
        const double max_angular_velocity = 2.5;

        // Get time
        int sec = msg->header.stamp.sec;
        int nanosec = msg->header.stamp.nanosec;

        double new_time = sec + nanosec / 1e9;

        // Get location
        double x = msg->location.x;
        double y = msg->location.y;
        printf("Time: %f\t x: %.2f\t y: %.2f\n", new_time, x, y);

        msgs::msg::Response response_msg;
        double time_diff = new_time - last_time;

        msgs::msg::Kinematics target;

        geometry_msgs::msg::Point target_location;
        target_location.x = x;
        target_location.y = y;
        target_location.z = 0.0;
        target.position = target_location;

        geometry_msgs::msg::Vector3 target_velocity;
        target_velocity.x = (x - lvtl.x) / time_diff;
        target_velocity.y = (y - lvtl.y) / time_diff;
        target_velocity.z = 0.0;
        target.velocity = target_velocity;

        // Check if this point is too far
        if (find_magnitude(target_velocity) > max_velocity)
        {
            target_velocity = scale_vector(target_velocity, max_velocity);
        }

        geometry_msgs::msg::Vector3 target_acceleration;
        target_acceleration.x = (target_velocity.x - target_last_velocity.x) / time_diff;
        target_acceleration.y = (target_velocity.y - target_last_velocity.y) / time_diff;
        target_acceleration.z = 0.0;
        target.acceleration = target_acceleration;

        // Check if getting to this point requires too much acceleration
        if (fabs(find_magnitude(target_acceleration)) > max_acceleration)
        {
            target_acceleration = scale_vector(target_acceleration, max_acceleration);
        }

        double target_angle = find_angle(target_velocity, target_last_velocity);
        target.angle = target_angle;
        double target_angular_velocity = target_angle / time_diff;
        target.anglular_velocity = target_angular_velocity;

        // Check if getting to this point has too much angle
        if (fabs(target_angular_velocity) > max_angular_velocity)
        {
            if (target_angular_velocity < 0)
            {
                target_angular_velocity = max_angular_velocity * -1;
            }
            else
            {
                target_angular_velocity = max_angular_velocity;
            }
            target_angle = target_angular_velocity * time_diff;
        }

        response_msg.target = target;

        response_msg.lvtl = lvtl;
        // Reconstruct target point using velocity and angle
        geometry_msgs::msg::Point new_point;
        if (location_history.size() < max_history)
        {
            new_point.x = lvtl.x + target_velocity.x * time_diff * std::cos(target_angle);
            new_point.y = lvtl.y + target_velocity.y * time_diff * std::sin(target_angle);
            new_point.z = 0.0;

            location_history.push_back({new_time, new_point});
        }
        else
        {
            std::vector<uint64_t> times;
            std::vector<geometry_msgs::msg::Point> points_x, points_y;

            for (const auto &pair : location_history)
            {
                times.push_back(pair.first);
                points_x.push_back(pair.second.x);
                points_y.push_back(pair.second.y);
            }

            CubicRegression cr_x, cr_y;
            cr_x.fit(times, points_x);
            cr_y.fit(times, points_y);

            new_point.x = cr_x.predict(new_time);
            new_point.y = cr_y.predict(new_time);
            new_point.z = 0.0;

            location_history.pop_front();
            location_history.push_back({new_time, new_point});
        }
        response_msg.target_location = new_point;

        // Simulate vehicle between lvtl and new point
        msgs::msg::Kinematics vehicle;

        vehicle.position = new_point;
        printf("\t\t new_x: %.2f\t new_y: %.2f\n", new_point.x, new_point.y);

        geometry_msgs::msg::Vector3 vehicle_velocity;
        vehicle_velocity.x = (new_point.x - lvtl.x) / time_diff;
        vehicle_velocity.y = (new_point.y - lvtl.y) / time_diff;
        vehicle_velocity.z = 0.0;
        vehicle.velocity = vehicle_velocity;

        geometry_msgs::msg::Vector3 vehicle_acceleration;
        vehicle_acceleration.x = (vehicle_velocity.x - vehicle_last_velocity.x) / time_diff;
        vehicle_acceleration.y = (vehicle_velocity.y - vehicle_last_velocity.y) / time_diff;
        vehicle_acceleration.z = 0.0;
        target.acceleration = vehicle_acceleration;

        double vehicle_angle = find_angle(vehicle_velocity, vehicle_last_velocity);
        vehicle.angle = vehicle_angle;
        double vehicle_angular_velocity = vehicle_angle / time_diff;
        vehicle.anglular_velocity = vehicle_angular_velocity;

        response_msg.vehicle = vehicle;

        // Reset last variables
        last_time = new_time;

        target_last_location = target_location;
        target_last_velocity = target_velocity;
        target_last_angle = target_angle;

        vehicle_last_location = new_point;
        vehicle_last_velocity = vehicle_velocity;
        vehicle_last_angle = vehicle_angle;

        lvtl = new_point;

        pub->publish(response_msg);
    }

    double find_angle(const geometry_msgs::msg::Vector3 &new_vec,
                      const geometry_msgs::msg::Vector3 &last_vec)
    {
        double dot_product = new_vec.x * last_vec.x + new_vec.y * last_vec.y;
        double magnitude_new_vec = find_magnitude(new_vec);
        double magnitude_last_vec = find_magnitude(last_vec);

        if (magnitude_new_vec == 0.0 || magnitude_last_vec == 0.0)
        {
            return 0.0;
        }

        double cos_theta = dot_product / (magnitude_new_vec * magnitude_last_vec);
        cos_theta = std::max(-1.0, std::min(1.0, cos_theta));
        double cross_product = new_vec.x * last_vec.y - new_vec.y * last_vec.x;
        double angle = std::atan2(cross_product, dot_product);

        return angle;
    }

    geometry_msgs::msg::Vector3 scale_vector(const geometry_msgs::msg::Vector3 &vec, double new_magnitude)
    {
        geometry_msgs::msg::Vector3 new_vec;
        double current_magnitude = find_magnitude(vec);
        if (current_magnitude == 0.0)
        {
            new_vec.x = 0.0;
            new_vec.y = 0.0;
            new_vec.z = 0.0;
        }
        else
        {
            double scale_factor = new_magnitude / current_magnitude;
            new_vec.x = vec.x * scale_factor;
            new_vec.y = vec.y * scale_factor;
            new_vec.z = vec.z * scale_factor;
        }
        return new_vec;
    }

    geometry_msgs::msg::Vector3 create_vector_from_points(const geometry_msgs::msg::Point &point_start,
                                                          const geometry_msgs::msg::Point &point_end)
    {
        geometry_msgs::msg::Vector3 vector;

        vector.x = point_end.x - point_start.x;
        vector.y = point_end.y - point_start.y;
        vector.z = 0.0;

        return vector;
    }

    double find_magnitude(geometry_msgs::msg::Vector3 vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }

    rclcpp::Subscription<msgs::msg::LocationStamped>::SharedPtr sub;
    rclcpp::Publisher<msgs::msg::Response>::SharedPtr pub;

    uint64_t last_time;

    geometry_msgs::msg::Point vehicle_last_location;
    geometry_msgs::msg::Vector3 vehicle_last_velocity;
    double vehicle_last_angle;

    geometry_msgs::msg::Point target_last_location;
    geometry_msgs::msg::Vector3 target_last_velocity;
    double target_last_angle;

    geometry_msgs::msg::Point lvtl;

    std::deque<std::pair<uint64_t, geometry_msgs::msg::Point>> location_history;
    size_t max_history;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LocationSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}