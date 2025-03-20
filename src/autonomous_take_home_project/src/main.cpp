#include <cmath>
#include <chrono>
#include <inttypes.h>

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

        last_time = 0;

        last_point_1.x = 0.0;
        last_point_1.y = 0.0;
        last_point_1.z = 0.0;

        last_point_2.x = 0.0;
        last_point_2.y = 0.0;
        last_point_2.z = 0.0;

        last_velocity.x = 0.0;
        last_velocity.y = 0.0;
        last_velocity.z = 0.0;
    }

private:
    void location_callback(const msgs::msg::LocationStamped::SharedPtr msg)
    {
        // Get time
        uint64_t sec = msg->header.stamp.sec;
        uint64_t nanosec = msg->header.stamp.nanosec;

        uint64_t new_time = sec * 1000000000 + nanosec;

        // Get location
        double x = msg->location.x;
        double y = msg->location.y;
        printf("Time: %" PRIu64 "\t x: %.2f\t y: %.2f\n", new_time, x, y);

        msgs::msg::Response response_msg;
        double time_diff = new_time - last_time;

        if (time_diff > 0)
        {
            geometry_msgs::msg::Point new_point;
            new_point.x = x;
            new_point.y = y;
            new_point.z = 0.0;

            geometry_msgs::msg::Vector3 new_velocity;
            new_velocity.x = (x - last_point_2.x) / time_diff;
            new_velocity.y = (y - last_point_2.y) / time_diff;
            new_velocity.z = 0.0;

            geometry_msgs::msg::Vector3 new_acceleration;
            new_acceleration.x = (new_velocity.x - last_velocity.x) / time_diff;
            new_acceleration.y = (new_velocity.y - last_velocity.y) / time_diff;
            new_acceleration.z = 0.0;

            // Create target
            msgs::msg::Kinematics target;

            target.position = new_point;
            target.velocity = new_velocity;
            target.acceleration = new_acceleration;

            double angle = find_angle(new_velocity, last_velocity);
            target.angle = angle;
            double angular_velocity = angle / time_diff;
            target.anglular_velocity = angular_velocity;

            response_msg.target = target;

            // printf("x: %.2f\t y: %.2f\t velocity: %.2f\t acc: %.2f\t angle: %.2f\t ang_v: %.2f\n", x, y, find_magnitude(new_velocity), find_magnitude(new_acceleration), angle, fabs(angular_velocity));
            const double max_speed = 10;
            const double max_acc = 2.5;
            const double max_ang_v = 2.5;

            if (is_valid(last_point_1, last_point_2, new_point) && find_magnitude(new_velocity) <= max_speed && find_magnitude(new_acceleration) <= max_acc && fabs(angular_velocity) <= max_ang_v)
            {
                lvtl = new_point;
                response_msg.lvtl = lvtl;
                response_msg.target_location = new_point;

                // Set valid vehicle points
            }
            else
            {
                response_msg.target_location = create_midpoint(lvtl, new_point);

                // Set invalid vehicle points
            }

            // Reset last variables
            last_time = new_time;
            last_point_1 = last_point_2; // Location at t-1 is now at t-2
            last_point_2 = new_point;    // Update new location to t-1

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
    geometry_msgs::msg::Point last_point_1; // This is at t-2
    geometry_msgs::msg::Point last_point_2; // This is at t-1
    geometry_msgs::msg::Vector3 last_velocity;
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