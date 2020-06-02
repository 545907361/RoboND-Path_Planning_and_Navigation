#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <visualization_msgs/Marker.h>
float goal_x = 0.0;
float goal_y = 0.0;
// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void goalmakr_callback(const visualization_msgs::Marker::ConstPtr& goalmakr_msg)
{
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "/map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal_x = goalmakr_msg->pose.position.x;
  goal_y = goalmakr_msg->pose.position.y;
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = goal_x;
  goal.target_pose.pose.position.y = goal_y;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending  goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to the 1st goal");
  else
    ROS_INFO("The base failed to move to the 1st goal for some reason");
  
  ros::Duration(5).sleep();
}
int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  //ROS_INFO("运行过了spin");
  /*
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  //move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "/map";
  goal.target_pose.header.stamp = ros::Time::now();
  */

  ros::Subscriber marker_sub = n.subscribe("visualization_marker", 1000, goalmakr_callback);
  ros::spin();
  /*
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = goal_x;
  goal.target_pose.pose.position.y = goal_y;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending 1st goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();
  
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to the 1st goal");
  else
    ROS_INFO("The base failed to move to the 1st goal for some reason");
  
  ros::Duration(5).sleep();
  */
  /*
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -4.0;
  goal.target_pose.pose.position.y = 5.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending 2nd goal");
  ac.sendGoal(goal);
  
  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved to the 2nd goal");
  else
    ROS_INFO("The base failed to moveto the 2nd goal for some reason");
  */
  
  return 0;
}