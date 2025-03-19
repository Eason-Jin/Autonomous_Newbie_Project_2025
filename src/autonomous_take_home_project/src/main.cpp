#include <cmath>
#include <chrono>

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

        last_time = rclcpp::Time(0, 0);
        geometry_msgs::msg::Point last_point_2;
        last_point_2.x = 0.0;
        last_point_2.y = 0.0;
        last_point_2.z = 0.0;
        geometry_msgs::msg::Vector3 last_velocity;
        last_velocity.x = 0.0;
        last_velocity.y = 0.0;
        last_velocity.z = 0.0;
    }

private:
    void location_callback(const msgs::msg::LocationStamped::SharedPtr msg)
    {
        // Get time
        int32_t sec = msg->header.stamp.sec;
        uint32_t nanosec = msg->header.stamp.nanosec;
        rclcpp::Time new_time = rclcpp::Time(sec, nanosec);

        // Get frame
        std::string frame_id = msg->header.frame_id;

        // Get location
        double x = msg->location.x;
        double y = msg->location.y;

        msgs::msg::Response response_msg;
        double time_diff = find_time_difference(new_time, last_time);
        geometry_msgs::msg::Point new_point;
        new_point.x = x;
        new_point.y = y;
        new_point.z = 0.0;

        geometry_msgs::msg::Vector3 new_velocity;
        new_velocity.x = (x - last_point_2.x) / time_diff;
        new_velocity.y = (y - last_point_2.y) / time_diff;
        new_velocity.z = 0.0;

        if (time_diff > 0)
        {
            response_msg.target = create_target(time_diff, new_point, new_velocity);

            bool valid = is_valid(last_point_1, last_point_2, new_point);
            if (valid)
            {
                lvtl = new_point;
                response_msg.lvtl = lvtl;
                response_msg.target_location = new_point;
            }
            else
            {
                response_msg.target_location = create_midpoint(lvtl, new_point);
            }

            // Create vehicle Kinematics

            // Reset last variables
            last_time = new_time;
            last_point_1 = last_point_2; // Location at t-1 is now at t-2
            last_point_2 = new_point;    // Update new location to t-1

            pub->publish(response_msg);
        }
    }

    msgs::msg::Kinematics create_target(double time_diff, geometry_msgs::msg::Point &new_point, geometry_msgs::msg::Vector3 &new_velocity)
    {
        msgs::msg::Kinematics target;

        target.position = new_point;

        target.velocity.x = new_velocity.x;
        target.velocity.y = new_velocity.y;
        target.velocity.z = 0.0;

        target.acceleration.x = (new_velocity.x - last_velocity.x) / time_diff;
        target.acceleration.y = (new_velocity.y - last_velocity.y) / time_diff;
        target.acceleration.z = 0.0;

        double angle_diff = find_angle_difference(new_velocity, last_velocity);
        target.angle = angle_diff;
        target.anglular_velocity = angle_diff / time_diff;
        return target;
    }

    double find_time_difference(rclcpp::Time &new_time, rclcpp::Time &last_time)
    {
        int32_t sec_diff = new_time.seconds() - last_time.seconds();
        int64_t nanosec_diff = static_cast<int64_t>(new_time.nanoseconds()) -
                               static_cast<int64_t>(last_time.nanoseconds());

        return sec_diff + nanosec_diff / 1e9;
    }

    double find_angle_difference(const geometry_msgs::msg::Vector3 &new_vec,
                                 const geometry_msgs::msg::Vector3 &last_vec)
    {
        double dot_product = new_vec.x * last_vec.x + new_vec.y * last_vec.y;
        double magnitude_new_vec = std::sqrt(new_vec.x * new_vec.x + new_vec.y * new_vec.y);
        double magnitude_last_vec = std::sqrt(last_vec.x * last_vec.x + last_vec.y * last_vec.y);

        if (magnitude_new_vec == 0.0 || magnitude_last_vec == 0.0)
        {
            return 0.0;
        }

        double cos_theta = dot_product / (magnitude_new_vec * magnitude_last_vec);
        cos_theta = std::max(-1.0, std::min(1.0, cos_theta));
        double cross_product = new_vec.x * last_vec.y - new_vec.y * last_vec.x;
        double angle = std::atan2(cross_product, dot_product) * (180.0 / M_PI);

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

    bool is_valid(geometry_msgs::msg::Point &p1, geometry_msgs::msg::Point &p2, geometry_msgs::msg::Point &p3)
    {
        // Consider the case for the first two points

        // Given 3 points {p1, p2, p3}, if angle between (p2-p1) and (p2-p3) is too small, this target is invalid
        const int threshold = 90;
        if ((find_angle_difference(create_vector_from_points(p2, p3), create_vector_from_points(p1, p2))) > threshold)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    rclcpp::Subscription<msgs::msg::LocationStamped>::SharedPtr sub;
    rclcpp::Publisher<msgs::msg::Response>::SharedPtr pub;

    geometry_msgs::msg::Point lvtl;
    geometry_msgs::msg::Point last_point_1; // This is at t-2
    geometry_msgs::msg::Point last_point_2; // This is at t-1
    geometry_msgs::msg::Vector3 last_velocity;
    rclcpp::Time last_time;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LocationSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}