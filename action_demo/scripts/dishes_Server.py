#! /usr/bin/env python

import roslib
roslib.load_manifest('action_demo')
import rospy
import actionlib

from action_demo.msg import DoDishesAction, DoDishesFeedback, DoDishesResult

class DoDishesServer:
    def __init__(self):
        self.server = actionlib.SimpleActionServer('do_dishes', DoDishesAction, self.execute, False)

        self.server.start()

    def execute(self, goal):
        rate = rospy.Rate(1) 
        feedback = DoDishesFeedback()

        rospy.loginfo("Dishwasher %d is working." % goal.dishwasher_id)
        
        for i in range(11):
            feedback.percent_complete = i * 10
            self.server.publish_feedback(feedback)
            rate.sleep()

        rospy.loginfo("Dishwasher %d finish working." % goal.dishwasher_id)

        result = DoDishesResult()
        result.total_dishes_cleaned = 10
        self.server.set_succeeded(result)


def server_action():
    rospy.init_node('do_dishes_server')
    server = DoDishesServer()
    rospy.spin()


if __name__=="__main__":
    server_action()