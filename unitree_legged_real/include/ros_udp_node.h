/**
 * @file ros_udp_node.h
 * @author Ziwen Zhuang (zhuangzw@sqz.ac.cn)
 * @brief The ros node run on NX to transport all robot proprioception and ros command
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _UNITREE_ROS_UDP_NODE_H_
#define _UNITREE_ROS_UDP_NODE_H_

#include "unitree_legged_sdk/unitree_legged_sdk.h"


class RosUdpHandler
{
public:
    std::string robot_namespace_;
    uint8_t ctrl_level;
    bool dryrun_;
    UNITREE_LEGGED_SDK::UDP udp;
    float udp_duration_;
    UNITREE_LEGGED_SDK::LoopFunc loop_udp_send;
    UNITREE_LEGGED_SDK::LoopFunc loop_udp_recv;
    
    UNITREE_LEGGED_SDK::Safety safe;

    UNITREE_LEGGED_SDK::HighCmd high_cmd_buffer = {0};
    UNITREE_LEGGED_SDK::HighState high_state_buffer = {0};

    UNITREE_LEGGED_SDK::LowCmd low_cmd_buffer = {0};
    UNITREE_LEGGED_SDK::LowState low_state_buffer = {0};

    ros::NodeHandle ros_handle;
    ros::Subscriber cmd_subscriber;
    ros::Publisher cmd_checker;
    ros::Publisher state_publisher;

protected:
    void udp_init(uint8_t level);
    void udp_start();
    void udp_send();
    void udp_recv();
    void high_cmd_callback(const unitree_legged_msgs::HighCmd::ConstPtr &msg);
    void low_cmd_callback(const unitree_legged_msgs::LowCmd::ConstPtr &msg);
    void high_state_publish();
    void low_state_publish();
    void publisher_init();
    void subscriber_init();

public:
    RosUdpHandler(
            const char* robot_namespace,
            const float udp_duration,
            uint8_t level,
            UNITREE_LEGGED_SDK::HighLevelType highControl,
            bool &dryrun
        );
};

#endif