#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>

void setPen(ros::ServiceClient &client, bool value)
{
    turtlesim::SetPen srv;
    srv.request.r = 0.0;
    srv.request.g = 0.0;
    srv.request.b = 0.0;
    srv.request.width = 3;
    srv.request.off = value;

    client.call(srv);
}

void teleportTo(ros::ServiceClient &client, double x, double y, double theta)
{
    turtlesim::TeleportAbsolute srv;
    srv.request.x = x;
    srv.request.y = y;
    srv.request.theta = theta;

    client.call(srv);
    ros::Duration(1.0).sleep();
}

void moveTurtle(ros::Publisher &controller_pub, double linear_x, double angular_z)
{
    geometry_msgs::Twist command;
    command.linear.x = linear_x;
    command.angular.z = angular_z;

    controller_pub.publish(command);
    ros::Duration(2.0).sleep();
}

void drawJ(ros::Publisher &controller_pub, ros::ServiceClient &tele_client, ros::ServiceClient &pen_client)
{
    setPen(pen_client, 1);
    teleportTo(tele_client, 0.31120967864990234, 10.674179077148438, 0.0);
    setPen(pen_client, 0);
    
    moveTurtle(controller_pub, 2.0, 0.0); 
    moveTurtle(controller_pub, 0.0, -1.5707963267); 

    moveTurtle(controller_pub, 2.2, 0.0); 
    moveTurtle(controller_pub, 0.0, 1.5707963267); 

    moveTurtle(controller_pub, 0.0, 3.1415926536); 
    moveTurtle(controller_pub, 2.1, 0.0); 
    moveTurtle(controller_pub, 0.0, -3.1415926536); 

    moveTurtle(controller_pub, 0.0, 1.5707963267);
    moveTurtle(controller_pub, 0.3, 0.0);
    setPen(pen_client, 1);
}

void drawA(ros::Publisher &controller_pub, ros::ServiceClient &tele_client, ros::ServiceClient &pen_client)
{
    teleportTo(tele_client, 3.839209794998169, 10.674179077148438, 4.1887902047863905);
    setPen(pen_client, 0);
    
    moveTurtle(controller_pub, 2.5, 0.0); 
    moveTurtle(controller_pub, -1.25, 0.0); 
    moveTurtle(controller_pub, 0.0, -4.1887902047863905);
    moveTurtle(controller_pub, 1.25, 0.0); 
    moveTurtle(controller_pub, 0.0, 5.235987755982988); 
    moveTurtle(controller_pub, 1.25, 0.0);
    moveTurtle(controller_pub, -2.5, 0.0);
    setPen(pen_client, 1);
}

void drawS(ros::Publisher &controller_pub, ros::ServiceClient &tele_client, ros::ServiceClient &pen_client)
{
    teleportTo(tele_client, 6.767791748046875, 6.956872463226318, 0.0);
    setPen(pen_client, 0);
    
    moveTurtle(controller_pub, -3.0, 0.0); 
    moveTurtle(controller_pub, 0.0, -1.5707963267); 

    moveTurtle(controller_pub, 1.5, 0.0); 
    moveTurtle(controller_pub, 0.0, 1.5707963267); 

    moveTurtle(controller_pub, 3.0, 0.0); 
    moveTurtle(controller_pub, 0.0, -1.5707963267); 

    moveTurtle(controller_pub, 1.5, 0.0); 
    moveTurtle(controller_pub, 0.0, 1.5707963267); 
    moveTurtle(controller_pub, 0.0, 3.1415926536); 
    moveTurtle(controller_pub, 3.0, 0.0); 
    
    setPen(pen_client, 1);
}

void drawO(ros::Publisher &controller_pub, ros::ServiceClient &tele_client, ros::ServiceClient &pen_client)
{
    teleportTo(tele_client, 5.212891101837158, 3.3151609897613525, 0.0);
    setPen(pen_client, 0);
    
    moveTurtle(controller_pub, 2.0, 0.0);
    moveTurtle(controller_pub, 0.0, -1.5707963267);

    moveTurtle(controller_pub, 2.5, 0.0);
    moveTurtle(controller_pub, 0.0, 1.5707963267);

    moveTurtle(controller_pub, -2.0, 0.0);
    moveTurtle(controller_pub, 0.0, 1.5707963267);

    moveTurtle(controller_pub, 2.5, 0.0);
    setPen(pen_client, 1);
}

void drawN(ros::Publisher &controller_pub, ros::ServiceClient &tele_client, ros::ServiceClient &pen_client)
{
    teleportTo(tele_client, 7.669558048248291, 3.3151609897613525, 5.497787143782138);
    setPen(pen_client, 0);
    

    moveTurtle(controller_pub, 3.5, 0.0); 
    moveTurtle(controller_pub, 0.0, -5.497787143782138); 
    moveTurtle(controller_pub, 0.0, 1.5707963267); 
    moveTurtle(controller_pub, 2.5, 0.0); 
    moveTurtle(controller_pub, -2.5, 0.0); 
    moveTurtle(controller_pub, 0.0, -1.5707963267); 
    moveTurtle(controller_pub, 0.0, 5.497787143782138);
    moveTurtle(controller_pub, -3.5, 0.0);
    moveTurtle(controller_pub, 0.0, -5.497787143782138);
    moveTurtle(controller_pub, 0.0, -1.5707963267);
    moveTurtle(controller_pub, 2.5, 0.0); 
    setPen(pen_client, 1);
}

int main(int argc, char * argv[])
{
    ros::init(argc, argv, "turtle_controller_node");
    ros::NodeHandle nh;
    ros::Publisher controller_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("turtle1/set_pen");
    ros::Rate loop_rate(10);

    ROS_INFO("Menggambar J");
    drawJ(controller_pub, teleport_client, pen_client);
    ROS_INFO("Selesai J, Menggambar A...");
    drawA(controller_pub, teleport_client, pen_client);
    ROS_INFO("Selesai A, Menggambar S...");
    drawS(controller_pub, teleport_client, pen_client);
    ROS_INFO("Selesai S, Menggambar O...");
    drawO(controller_pub, teleport_client, pen_client);
    ROS_INFO("Selesai O, Menggambar N...");
    drawN(controller_pub, teleport_client, pen_client);
    ROS_INFO("Selesai N");

    ros::spin();
    ros::shutdown();
    return 0;
}
