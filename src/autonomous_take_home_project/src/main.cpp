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

        target_last_location.x = 0.0;
        target_last_location.y = 0.0;
        target_last_location.z = 0.0;

        target_last_velocity.x = 0.0;
        target_last_velocity.y = 0.0;
        target_last_velocity.z = 0.0;

        lvtl = vehicle_last_location;

        locations.push_back(vehicle_last_location);
        max_locations = 3;
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

        locations.push_back(msg->location);
        if (locations.size() > max_locations)
        {
            locations.pop_front();
        }
        // The car does not start until it has 3 locations
        if (locations.size() < max_locations)
        {
            response_msg.target.position = msg->location;
            response_msg.target.velocity = target_last_velocity;
            response_msg.target.acceleration.x = 0.0;
            response_msg.target.acceleration.y = 0.0;
            response_msg.target.acceleration.z = 0.0;
            response_msg.target.angle = 0.0;
            response_msg.target.anglular_velocity = 0.0;
            response_msg.lvtl = lvtl;
            response_msg.target_location = lvtl;
            response_msg.vehicle.position = vehicle_last_location;
            response_msg.vehicle.velocity = vehicle_last_velocity;
            response_msg.vehicle.acceleration.x = 0.0;
            response_msg.vehicle.acceleration.y = 0.0;
            response_msg.vehicle.acceleration.z = 0.0;
            response_msg.vehicle.angle = 0.0;
            response_msg.vehicle.anglular_velocity = 0.0;
            pub->publish(response_msg);
            return;
        }

        // Now there should be 3 locations in locations, past, now, next
        // If now is invalid (i.e. angle between (now-past) and (next-now) is too large)
        // then we interpolate between past and next, this new point becomes now
        // The vehicle is at past trying to move to now
        double time_diff = new_time - last_time;
        geometry_msgs::msg::Point past = locations[0];
        geometry_msgs::msg::Point now = locations[1];
        geometry_msgs::msg::Point next = locations[2];

        geometry_msgs::msg::Vector3 past_to_now = create_vector_from_points(past, now);
        geometry_msgs::msg::Vector3 now_to_next = create_vector_from_points(now, next);

        double angle = find_angle(past_to_now, now_to_next);
        double angular_velocity = angle / time_diff;
        if (fabs(angular_velocity) > max_angular_velocity)
        {
            // Interpolate between past and next
            double new_x = past.x + (next.x - past.x) / 2;
            double new_y = past.y + (next.y - past.y) / 2;
            now.x = new_x;
            now.y = new_y;
        }

        msgs::msg::Kinematics target;

        geometry_msgs::msg::Point target_location;
        target_location.x = now.x;
        target_location.y = now.y;
        target_location.z = 0.0;
        target.position = target_location;

        geometry_msgs::msg::Vector3 target_velocity;
        target_velocity.x = (now.x - lvtl.x) / time_diff;
        target_velocity.y = (now.y - lvtl.y) / time_diff;
        target_velocity.z = 0.0;
        target.velocity = target_velocity;

        geometry_msgs::msg::Vector3 target_acceleration;
        target_acceleration.x = (target_velocity.x - target_last_velocity.x) / time_diff;
        target_acceleration.y = (target_velocity.y - target_last_velocity.y) / time_diff;
        target_acceleration.z = 0.0;
        target.acceleration = target_acceleration;

        // Check if getting to this point requires too much acceleration
        double target_angle = find_angle(target_velocity, target_last_velocity);
        target.angle = target_angle;
        response_msg.target = target;

        // Simulate vehicle from lvtl
        msgs::msg::Kinematics vehicle;

        geometry_msgs::msg::Vector3 vehicle_velocity;
        if (find_magnitude(target_velocity) > max_velocity)
        {
            vehicle_velocity = scale_vector(target_velocity, max_velocity);
            // Recalculate location
            now.x = lvtl.x + vehicle_velocity.x * time_diff;
            now.y = lvtl.y + vehicle_velocity.y * time_diff;
        }
        else
        {
            vehicle_velocity = target_velocity;
        }
        vehicle.velocity = vehicle_velocity;

        geometry_msgs::msg::Point vehicle_location;
        vehicle_location = now;
        vehicle.position = vehicle_location;

        geometry_msgs::msg::Vector3 vehicle_acceleration;
        if (fabs(find_magnitude(target_acceleration)) > max_acceleration)
        {
            vehicle_acceleration = scale_vector(target_acceleration, max_acceleration);
        }
        else
        {
            vehicle_acceleration = target_acceleration;
        }
        vehicle.acceleration = vehicle_acceleration;

        double vehicle_angle = find_angle(vehicle_velocity, vehicle_last_velocity);
        vehicle.angle = vehicle_angle;
        double vehicle_angular_velocity = vehicle_angle / time_diff;
        vehicle.anglular_velocity = vehicle_angular_velocity;
        response_msg.vehicle = vehicle;

        response_msg.lvtl = lvtl;
        response_msg.target_location = now;

        // Reset last variables
        last_time = new_time;

        target_last_location = target_location;
        target_last_velocity = target_velocity;

        vehicle_last_location = vehicle_location;
        vehicle_last_velocity = vehicle_velocity;

        lvtl = now;
        printf("\t\tnow.x: %.2f\t now.y: %.2f\n", now.x, now.y);

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

    geometry_msgs::msg::Point target_last_location;
    geometry_msgs::msg::Vector3 target_last_velocity;

    std::deque<geometry_msgs::msg::Point> locations; // Last, now, next
    size_t max_locations;

    geometry_msgs::msg::Point lvtl; // Last valid target location
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LocationSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}