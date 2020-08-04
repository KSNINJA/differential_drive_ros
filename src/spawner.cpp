#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <termio.h>
#include "std_msgs/Float32.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

void spawnerCallback(const geometry_msgs::Twist& res)
{
     _Float64 speed = 5;
     ros::NodeHandle n1;
     ros::Publisher right_wheel = n1.advertise<std_msgs::Float64>("/diff_drive/right_wheel_velocity_controller/command", 1000);
     ros::Publisher left_wheel = n1.advertise<std_msgs::Float64>("/diff_drive/left_wheel_velocity_controller/command", 1000);
     std_msgs::Float64 left_wheel_vel;
     std_msgs::Float64 right_wheel_vel;
     ros::Rate loop_rate(1);
     if(res.linear.x == 2){
        left_wheel_vel.data = speed;
        right_wheel_vel.data = speed;
        while(ros::ok()){
            left_wheel.publish(left_wheel_vel);
            right_wheel.publish(right_wheel_vel);
            ROS_INFO("published message");
            ros::spinOnce();
            loop_rate.sleep();
        }
     }
     else if(res.linear.x == -2){
        left_wheel_vel.data = -1*speed;
        right_wheel_vel.data = -1*speed;
        while(ros::ok()){
            left_wheel.publish(left_wheel_vel);
            right_wheel.publish(right_wheel_vel);
            ROS_INFO("published message");
            ros::spinOnce();
            loop_rate.sleep();
        }
     }
     else if(res.angular.z == 2){
        left_wheel_vel.data = 0;
        right_wheel_vel.data = speed;
        while(ros::ok()){
            left_wheel.publish(left_wheel_vel);
            right_wheel.publish(right_wheel_vel);
            ROS_INFO("published message");
            ros::spinOnce();
            loop_rate.sleep();
        }
     } 
     else if(res.angular.z == -2){
        left_wheel_vel.data = speed;
        right_wheel_vel.data = 0;
        while(ros::ok()){
            left_wheel.publish(left_wheel_vel);
            right_wheel.publish(right_wheel_vel);
            ROS_INFO("published message");
            ros::spinOnce();
            loop_rate.sleep();
        }
     }    
     
}

int main(int argc, char **argv){
    ros::init(argc, argv, "spawner");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/turtle1/cmd_vel", 1, spawnerCallback);
    ros::spin();
    return 0;
    
}