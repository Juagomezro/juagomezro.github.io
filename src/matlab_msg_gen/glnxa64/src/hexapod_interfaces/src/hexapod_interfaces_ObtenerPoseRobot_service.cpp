// Copyright 2021-2022 The MathWorks, Inc.
// Common copy functions for hexapod_interfaces/ObtenerPoseRobotRequest
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100)
#pragma warning(disable : 4265)
#pragma warning(disable : 4456)
#pragma warning(disable : 4458)
#pragma warning(disable : 4946)
#pragma warning(disable : 4244)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif //_MSC_VER
#include "rclcpp/rclcpp.hpp"
#include "hexapod_interfaces/srv/obtener_pose_robot.hpp"
#include "visibility_control.h"
#ifndef FOUNDATION_MATLABDATA_API
#include "MDArray.hpp"
#include "StructArray.hpp"
#include "TypedArrayRef.hpp"
#include "Struct.hpp"
#include "ArrayFactory.hpp"
#include "StructRef.hpp"
#include "Reference.hpp"
#endif
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
#include "ROS2ServiceTemplates.hpp"
class HEXAPOD_INTERFACES_EXPORT ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common : public MATLABROS2MsgInterface<hexapod_interfaces::srv::ObtenerPoseRobot::Request> {
  public:
    virtual ~ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common(){}
    virtual void copy_from_struct(hexapod_interfaces::srv::ObtenerPoseRobot::Request* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const hexapod_interfaces::srv::ObtenerPoseRobot::Request* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common::copy_from_struct(hexapod_interfaces::srv::ObtenerPoseRobot::Request* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common::get_arr(MDFactory_T& factory, const hexapod_interfaces::srv::ObtenerPoseRobot::Request* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("hexapod_interfaces/ObtenerPoseRobotRequest");
    }
    return std::move(outArray);
  }
class HEXAPOD_INTERFACES_EXPORT ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common : public MATLABROS2MsgInterface<hexapod_interfaces::srv::ObtenerPoseRobot::Response> {
  public:
    virtual ~ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common(){}
    virtual void copy_from_struct(hexapod_interfaces::srv::ObtenerPoseRobot::Response* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    virtual MDArray_T get_arr(MDFactory_T& factory, const hexapod_interfaces::srv::ObtenerPoseRobot::Response* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common::copy_from_struct(hexapod_interfaces::srv::ObtenerPoseRobot::Response* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //x
        const matlab::data::TypedArray<float> x_arr = arr["x"];
        msg->x = x_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'x' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'x' is wrong type; expected a single.");
    }
    try {
        //y
        const matlab::data::TypedArray<float> y_arr = arr["y"];
        msg->y = y_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'y' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'y' is wrong type; expected a single.");
    }
    try {
        //angle
        const matlab::data::TypedArray<float> angle_arr = arr["angle"];
        msg->angle = angle_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'angle' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'angle' is wrong type; expected a single.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common::get_arr(MDFactory_T& factory, const hexapod_interfaces::srv::ObtenerPoseRobot::Response* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","x","y","angle"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("hexapod_interfaces/ObtenerPoseRobotResponse");
    // x
    auto currentElement_x = (msg + ctr)->x;
    outArray[ctr]["x"] = factory.createScalar(currentElement_x);
    // y
    auto currentElement_y = (msg + ctr)->y;
    outArray[ctr]["y"] = factory.createScalar(currentElement_y);
    // angle
    auto currentElement_angle = (msg + ctr)->angle;
    outArray[ctr]["angle"] = factory.createScalar(currentElement_angle);
    }
    return std::move(outArray);
  } 
class HEXAPOD_INTERFACES_EXPORT ros2_hexapod_interfaces_ObtenerPoseRobot_service : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_hexapod_interfaces_ObtenerPoseRobot_service(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABSvcServerInterface> generateSvcServerInterface();
    virtual std::shared_ptr<MATLABSvcClientInterface> generateSvcClientInterface();
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_hexapod_interfaces_ObtenerPoseRobot_service::generatePublisherInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2PublisherImpl<hexapod_interfaces::srv::ObtenerPoseRobot::Request,ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2PublisherImpl<hexapod_interfaces::srv::ObtenerPoseRobot::Response,ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSubscriberInterface> 
          ros2_hexapod_interfaces_ObtenerPoseRobot_service::generateSubscriberInterface(ElementType type){
    if(type == eRequest){
        return std::make_shared<ROS2SubscriberImpl<hexapod_interfaces::srv::ObtenerPoseRobot::Request,ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common>>();
    }else if(type == eResponse){
        return std::make_shared<ROS2SubscriberImpl<hexapod_interfaces::srv::ObtenerPoseRobot::Response,ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<void> ros2_hexapod_interfaces_ObtenerPoseRobot_service::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
        auto msg = std::make_shared<hexapod_interfaces::srv::ObtenerPoseRobot::Request>();
        ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResponse){
        auto msg = std::make_shared<hexapod_interfaces::srv::ObtenerPoseRobot::Response>();
        ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
  std::shared_ptr<MATLABSvcServerInterface> 
          ros2_hexapod_interfaces_ObtenerPoseRobot_service::generateSvcServerInterface(){
    return std::make_shared<ROS2SvcServerImpl<hexapod_interfaces::srv::ObtenerPoseRobot,hexapod_interfaces::srv::ObtenerPoseRobot::Request,hexapod_interfaces::srv::ObtenerPoseRobot::Response,ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common,ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common>>();
  }
  std::shared_ptr<MATLABSvcClientInterface> 
          ros2_hexapod_interfaces_ObtenerPoseRobot_service::generateSvcClientInterface(){
    return std::make_shared<ROS2SvcClientImpl<hexapod_interfaces::srv::ObtenerPoseRobot,hexapod_interfaces::srv::ObtenerPoseRobot::Request,hexapod_interfaces::srv::ObtenerPoseRobot::Response,ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common,ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common,rclcpp::Client<hexapod_interfaces::srv::ObtenerPoseRobot>::SharedFuture>>();
  }
  matlab::data::StructArray ros2_hexapod_interfaces_ObtenerPoseRobot_service::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eRequest){
	    ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (hexapod_interfaces::srv::ObtenerPoseRobot::Request*)msgPtr, loader);
    }else if(type == eResponse){
        ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;	
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (hexapod_interfaces::srv::ObtenerPoseRobot::Response*)msgPtr, loader);
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Request' or 'Response'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_hexapod_interfaces_msg_ObtenerPoseRobotRequest_common, MATLABROS2MsgInterface<hexapod_interfaces::srv::ObtenerPoseRobot::Request>)
CLASS_LOADER_REGISTER_CLASS(ros2_hexapod_interfaces_msg_ObtenerPoseRobotResponse_common, MATLABROS2MsgInterface<hexapod_interfaces::srv::ObtenerPoseRobot::Response>)
CLASS_LOADER_REGISTER_CLASS(ros2_hexapod_interfaces_ObtenerPoseRobot_service, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1
