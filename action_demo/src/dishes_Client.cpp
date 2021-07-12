#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include "action_demo/DoDishesAction.h"

typedef actionlib::SimpleActionClient<action_demo::DoDishesAction> Client;

// execute when the goal is done
void doneCb(const actionlib::SimpleClientGoalState& state,
        const action_demo::DoDishesResultConstPtr& result)
{
    ROS_INFO("Yay! The dishes(%d) are now clean", result->total_dishes_cleaned);
}

// execute when the goal is active
void activeCb()
{
    ROS_INFO("Goal just went active");
}

// execute when receiving the feedback from server
void feedbackCb(const action_demo::DoDishesFeedbackConstPtr& feedback)
{
    ROS_INFO(" percent_complete : %f ", feedback->percent_complete);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "do_dishes_client");

    // create a client
    Client client("do_dishes", true);

    // wait for server
    ROS_INFO("Waiting for action server to start.");
    client.waitForServer();
    ROS_INFO("Action server started, sending goal.");

    // create goal
    action_demo::DoDishesGoal goal;
    goal.dishwasher_id = 1;

    // send goal to server. set callback
    client.sendGoal(goal,  &doneCb, &activeCb, &feedbackCb);

    client.waitForResult();

    ros::Duration(1).sleep();

    return 0;
}