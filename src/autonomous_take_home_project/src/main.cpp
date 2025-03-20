#include <cmath>
#include <chrono>
#include <algorithm>

#include <rclcpp/rclcpp.hpp>
#include <msgs/msg/location_stamped.hpp>
#include <msgs/msg/response.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/vector3.hpp>

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

        vehicle_last_acceleration.x = 0.0;
        vehicle_last_acceleration.y = 0.0;
        vehicle_last_acceleration.z = 0.0;

        vehicle_last_angle = 0.0;

        target_last_location.x = 0.0;
        target_last_location.y = 0.0;
        target_last_location.z = 0.0;

        target_last_velocity.x = 0.0;
        target_last_velocity.y = 0.0;
        target_last_velocity.z = 0.0;

        target_last_acceleration.x = 0.0;
        target_last_acceleration.y = 0.0;
        target_last_acceleration.z = 0.0;

        target_last_angle = 0.0;

        lvtl = vehicle_last_location;
    }

private:
    void location_callback(const msgs::msg::LocationStamped::SharedPtr msg)
    {
        const double max_velocity = 10;
        const double max_acceleration = 2.5;
        const double max_angular_velocity = 2.5;

        // Get time
        uint64_t sec = msg->header.stamp.sec;
        uint64_t nanosec = msg->header.stamp.nanosec;

        double new_time = sec + nanosec / 1000000000;

        // Get location
        double x = msg->location.x;
        double y = msg->location.y;
        printf("Time: %.9f\t x: %.2f\t y: %.2f\n", new_time, x, y);

        msgs::msg::Response response_msg;
        double time_diff = new_time - last_time;

        // It will always be true, but just in case realistically
        if (time_diff > 0)
        {
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
            if (target_velocity > max_velocity)
            {
                target_velocity = max_velocity;
            }

            geometry_msgs::msg::Vector3 target_acceleration;
            target_acceleration.x = (target_velocity.x - target_last_velocity.x) / time_diff;
            target_acceleration.y = (target_velocity.y - target_last_velocity.y) / time_diff;
            target_acceleration.z = 0.0;
            target.acceleration = target_acceleration;

            // Check if getting to this point requires too much acceleration
            if (fabs(target_acceleration) > max_acceleration)
            {
                if (target_acceleration < 0)
                {
                    target_acceleration = max_acceleration * -1;
                }
                else
                {
                    target_acceleration = max_acceleration;
                }
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
            new_point.x = lvtl.x + target_velocity * time_diff * std::cos(target_angle);
            new_point.y = lvtl.y + target_velocity * time_diff * std::sin(target_angle);
            new_point.z = 0.0;
            response_msg.target_location = new_point;
            
            printf("lvtl: {%.2f, %.2f},\t target_location: {%.2f, %.2f}", lvtl.x, lvtl.y, new_point.x, new_point.y);
            // Simulate vehicle between lvtl and new point

            // Reset last variables
            last_time = new_time;

            target_last_location = target_location;
            target_last_velocity = target_velocity;
            target_last_acceleration = target_acceleration;
            target_last_angle = target_angle;

            lvtl = new_point;

            pub->publish(response_msg);
        }
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
    geometry_msgs::msg::Vector3 create_vector_from_points(const geometry_msgs::msg::Point &point_start,
                                                          const geometry_msgs::msg::Point &point_end)
    {
        geometry_msgs::msg::Vector3 vector;

        vector.x = point_end.x - point_start.x;
        vector.y = point_end.y - point_start.y;
        vector.z = 0.0;

        return vector;
    }
    geometry_msgs::msg::Point create_midpoint(const geometry_msgs::msg::Point &point1, const geometry_msgs::msg::Point &point2)
    {
        geometry_msgs::msg::Point midpoint;

        midpoint.x = (point1.x + point2.x) / 2.0;
        midpoint.y = (point1.y + point2.y) / 2.0;
        midpoint.z = 0.0;

        return midpoint;
    }

    double find_magnitude(geometry_msgs::msg::Vector3 vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }

    bool is_valid(geometry_msgs::msg::Point &p1, geometry_msgs::msg::Point &p2, geometry_msgs::msg::Point &p3)
    {
        // Consider the case for the first time
        geometry_msgs::msg::Vector3 vec1 = create_vector_from_points(p2, p3);
        geometry_msgs::msg::Vector3 vec2 = create_vector_from_points(p1, p2);
        double magnitude_vec1 = find_magnitude((vec1));
        double magnitude_vec2 = find_magnitude(vec2);
        if (magnitude_vec1 == 0.0 || magnitude_vec2 == 0.0)
        {
            return true;
        }

        // Given 3 points {p1, p2, p3}, if angle between (p2-p1) and (p2-p3) is too small, this target is invalid
        const int threshold = 2.5; // From the brief
        return (fabs(find_angle(vec1, vec2)) <= threshold) ? true : false;
    }
    rclcpp::Subscription<msgs::msg::LocationStamped>::SharedPtr sub;
    rclcpp::Publisher<msgs::msg::Response>::SharedPtr pub;

    uint64_t last_time;

    geometry_msgs::msg::Point vehicle_last_location;
    geometry_msgs::msg::Vector3 vehicle_last_velocity;
    geometry_msgs::msg::Vector3 vehicle_last_acceleration;
    double vehicle_last_angle;

    geometry_msgs::msg::Point target_last_location;
    geometry_msgs::msg::Vector3 target_last_velocity;
    geometry_msgs::msg::Vector3 target_last_acceleration;
    double target_last_angle;

    geometry_msgs::msg::Point lvtl;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LocationSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}