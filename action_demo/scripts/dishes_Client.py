#!/usr/bin/env python
# coding:utf-8

import roslib
roslib.load_manifest('action_demo')
import rospy
import actionlib

from action_demo.msg import DoDishesAction, DoDishesGoal

def done_cb(status, result):
    rospy.loginfo("Yay! The dishes(%d) are now clean" % result.total_dishes_cleaned)

def active_cb():
    rospy.loginfo("Goal just went active")

def feedback_cb(feedback):
    rospy.loginfo(" percent_complete : %f " % feedback.percent_complete)

def client_action():
    rospy.init_node('do_dishes_client')
    client = actionlib.SimpleActionClient('do_dishes', DoDishesAction)

    rospy.loginfo("Waiting for action server to start.")
    client.wait_for_server()
    rospy.loginfo("Action server started, sending goal.")

    goal = DoDishesGoal()
    goal.dishwasher_id = 1

    client.send_goal(goal, done_cb, active_cb, feedback_cb)

    client.wait_for_result()

    rospy.sleep(rospy.Duration(1))   


if __name__=="__main__":
    client_action()