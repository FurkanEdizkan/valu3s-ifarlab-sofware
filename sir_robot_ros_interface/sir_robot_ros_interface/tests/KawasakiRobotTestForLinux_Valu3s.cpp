#define ROBOTFORLINUXTEST
#ifdef ROBOTFORLINUXTEST


#include "KawasakiRS005LRobot.h"
#include "SIRLinConnection.h"
#include "SIRTypeDefs.h"
#include "khi_ota_comm_valu3s.h"
#include <sir_robot_ros_interface/ManipulatorPose.h>
#include <iostream>
#include <vector>
#include <StdVector>
EIGEN_DEFINE_STL_VECTOR_SPECIALIZATION(SIRMatrix)

using namespace std;
  SIRLogger *logger = new SIRLogger("log.txt", SIRLOGLEVEL::LOGLEVEL_DEBUG);
  SIRConnection *con = new SIRLinConnection(logger,"192.168.3.7",11111);
  KawasakiRS005LRobot robot(con, logger,nullptr, MPT_TASK, MT_LINEAR);




OTA_STATE state = OTA_STATE_WAIT;



vector<SIRMatrix> pathPlanner(string pose_data){

    vector<SIRMatrix> path;

    SIRMatrix P_Top_Box(6,1);
    SIRMatrix P_Top_Vehicle(6,1);
    SIRMatrix P_Home(6,1);

    SIRMatrix P_Grip(6,1);     //200x200x200
    SIRMatrix P_Before_Grip(6,1);
    SIRMatrix P_Before_Drop(6,1);
    SIRMatrix P_Drop(6,1);

    SIRMatrix P_Grip2(6,1);    //250x250x350
    SIRMatrix P_Before_Grip2(6,1); //
    SIRMatrix P_Before_Drop2(6,1);
    SIRMatrix P_Drop2(6,1);


    P_Home<<-14.793, 291.511, 479.387, 85.348, 178.828, 153.068;
//    P_Before_Grip<<1.291, 272.112, 555.659, 89.330, 88.264, 159.451;
    P_Before_Grip<<1.596, 429.397, 669.167, 89.327, 83.440, 159.499;
    P_Before_Drop<<1.596, 670.271, 403.231, 89.373, 135.451, 159.910;


    // B is for small box
    if(pose_data == "camera"){
        path.push_back(P_Before_Grip);
        path.push_back(P_Before_Drop);
    }
    if(pose_data == "home"){

        path.push_back(P_Home);
    }
    return path;
}

bool add(sir_robot_ros_interface::ManipulatorPose::Request  &req,
         sir_robot_ros_interface::ManipulatorPose::Response &res)
{
    if(state==OTA_STATE_WAIT){

      if((req.pose == "home") || (req.pose == "camera")){
        std::cout << "OTA has arrived" << std::endl;
        state = OTA_STATE_OPERATE;
      }
      else{
        std::cout << "Waiting for OTA arrival" << std::endl;
      }

    }
    if(state==OTA_STATE_OPERATE){
        if (!robot.Connect()) {
            cout << "Could not connect to robot..." << endl;
            return 0;
        }
        else
            cout << "Connected..." << endl;
        //********* CONNECTED **************
        con->setBlockingMode(0);
        robot.setWaitForCommand(2000);
        sleep(2);
        vector<SIRMatrix> path = pathPlanner(req.pose);

        //open Gripper
        if (robot.setSignal(1,false))
            cout << "success to set signal..." << endl;
        else{
            cout << "fail to set signal..." << endl;
            res.status = "abort";
            return true;
        }
        if (robot.setSignal(2,false))
            cout << "success to set signal..." << endl;
        else{
            cout << "fail to set signal..." << endl;
            res.status = "abort";
            return true;
        }
        if (robot.setSignal(1,true))
            cout << "success to set signal..." << endl;
        else{
            cout << "fail to set signal..." << endl;
            res.status = "abort";
            return true;
        }
        if (req.pose == "camera"){
          for(int i=0;i<2;i++)
          {
            cout << "send packet id: " << robot.add(path[i]) << endl;
          }
        }
        else if (req.pose == "home"){
          cout << "send packet id: " << robot.add(path[0]) << endl;
        }
        if (robot.move())
            cout << "the robot is moving" << endl;
        else{
            cout << "the robot is not moving" << endl;
            res.status = "abort";
            return true;
        }
        //hareketin bitimini bekle...
        while(robot.getStatus()!=RS_STOP){
            bool sigValue;
            cout<<robot.getSignal(1,sigValue)<<endl;
            sleep(1);
        }
            cout<<robot.getStatus()<<endl;
        if (robot.setSignal(1,false))
            cout << "success to set signal..." << endl;
        else{
            cout << "fail to set signal..." << endl;
            res.status = "abort";
            return true;
        }
        sleep(2);

        if (robot.close())
            cout << "The connection is succesfully closed..." << endl;
        else{
            cout << "The connection is not succesfully closed..." << endl;
            res.status = "abort";
            return true;
        }
        //**********************************
        state = OTA_STATE_FINISH;

    }

    if(state == OTA_STATE_FINISH){
        ros::Duration(1.0).sleep();
        state = OTA_STATE_WAIT;
        res.status = "succeed";
    }
  return true;
}

int main(int argc, char **argv) {


  //SIRConnection *con = new SIRLinConnection(logger,"127.0.0.1",7777);
  //con->setBlockingMode(1);

  ros::init(argc, argv, "khi_ota_comm");

  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("manipulator_service", add);

  ros::spin();
  return 0;
}

#endif

