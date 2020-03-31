#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "action_demo/DoDishesAction.h"

typedef actionlib::SimpleActionServer<action_demo::DoDishesAction> Server;

// execute when receive a goal from client
void execute(const action_demo::DoDishesGoalConstPtr& goal, Server* as)
{
    ros::Rate rate(1);
    action_demo::DoDishesFeedback feedback;

    ROS_INFO("Dishwasher %d is working.", goal->dishwasher_id);

    // publish feedback
    for(int i=1; i<=10; i++) {
        feedback.percent_complete = i * 10;
        as->publishFeedback(feedback);
        rate.sleep();
    }

    // done. return result
    ROS_INFO("Dishwasher %d finish working.", goal->dishwasher_id);
    action_demo::DoDishesResult result;
    result.total_dishes_cleaned = 10;
    as->setSucceeded(result);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "do_dishes_server");
    ros::NodeHandle nh;

    // create a server
    Server server(nh, "do_dishes", boost::bind(&execute, _1, &server), false);

    // start the server
    server.start();

    ros::spin();

    return 0;
}