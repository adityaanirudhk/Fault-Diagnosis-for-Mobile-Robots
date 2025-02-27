   #include "rclcpp/rclcpp.hpp"
   #include "tf2_ros/transform_broadcaster.h"

   #include "std_msgs/msg/string.hpp"
   #include "geometry_msgs/msg/twist.hpp"
   #include "nav_msgs/msg/odometry.hpp"
   #include <sstream>


static geometry_msgs::msg::Twist velocity;
//static nav_msgs::ms::Odometry get_odom;
static nav_msgs::msg::Odometry fake;

float X,Y;

using namespace std::chrono_literals;

class fake_odom : public rclcpp::Node
{
public:
  fake_odom()
  : Node("fake_odom"), count_(0)
  {
     //pub_fakeodom_ = this->create_publisher<nav_msgs::msg::Odometry>("odom");
     pub_fakeodom_ = this->create_publisher<nav_msgs::msg::Odometry>("odom");
  }
  void handle_communication() {
fake.pose.pose.position.x=2.0;
this->pub_fakeodom_->publish(fake);


  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_fakeodom_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  std::shared_ptr<fake_odom> node(std::make_shared<fake_odom>());
  while (rclcpp::ok())
  {
    node->handle_communication();
    rclcpp::spin_some(node);
  }
  return 0;
}








/*  
int main(int argc, char** argv){
     ros::init(argc, argv, "odometry_publisher");
   
     ros::NodeHandle n;
     ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
     tf::TransformBroadcaster odom_broadcaster;
   
     double x = 0.0;
     double y = 0.0;
     double th = 0.0;
   
     double vx = 0.1;
     double vy = -0.1;
     double vth = 0.1;
   
     ros::Time current_time, last_time;
     current_time = ros::Time::now();
     last_time = ros::Time::now();
   
     ros::Rate r(1.0);
     while(n.ok()){
   
       ros::spinOnce();               // check for incoming messages
       current_time = ros::Time::now();
   
       //compute odometry in a typical way given the velocities of the robot
       double dt = (current_time - last_time).toSec();
       double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
       double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
       double delta_th = vth * dt;
   
       x += delta_x;
       y += delta_y;
       th += delta_th;
   
       //since all odometry is 6DOF we'll need a quaternion created from yaw
       geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
   
       //first, we'll publish the transform over tf
       geometry_msgs::TransformStamped odom_trans;
       odom_trans.header.stamp = current_time;
       odom_trans.header.frame_id = "odom";
       odom_trans.child_frame_id = "base_link";
   
       odom_trans.transform.translation.x = x;
       odom_trans.transform.translation.y = y;
       odom_trans.transform.translation.z = 0.0;
       odom_trans.transform.rotation = odom_quat;
   
      //send the transform
       odom_broadcaster.sendTransform(odom_trans);
   
      //next, we'll publish the odometry message over ROS
       nav_msgs::Odometry odom;
      odom.header.stamp = current_time;
     odom.header.frame_id = "odom";
  
      //set the position
      odom.pose.pose.position.x = x;
      odom.pose.pose.position.y = y;
      odom.pose.pose.position.z = 0.0;
      odom.pose.pose.orientation = odom_quat;
   
      //set the velocity
       odom.child_frame_id = "base_link";
       odom.twist.twist.linear.x = vx;
       odom.twist.twist.linear.y = vy;
       odom.twist.twist.angular.z = vth;
   
       //publish the message
       odom_pub.publish(odom);
   
       last_time = current_time;
       r.sleep();
     }
   }
*/
   
   