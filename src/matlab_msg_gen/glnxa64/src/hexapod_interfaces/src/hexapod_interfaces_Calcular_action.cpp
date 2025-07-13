// Copyright 2022 The MathWorks, Inc.
// Common copy functions for hexapod_interfaces/CalcularGoal
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
#include "hexapod_interfaces/action/calcular.hpp"
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
#include "ROS2ActionTemplates.hpp"
class HEXAPOD_INTERFACES_EXPORT hexapod_interfaces_msg_CalcularGoal_common : public MATLABROS2MsgInterface<hexapod_interfaces::action::Calcular::Goal> {
  public:
    virtual ~hexapod_interfaces_msg_CalcularGoal_common(){}
    virtual void copy_from_struct(hexapod_interfaces::action::Calcular::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const hexapod_interfaces::action::Calcular::Goal* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void hexapod_interfaces_msg_CalcularGoal_common::copy_from_struct(hexapod_interfaces::action::Calcular::Goal* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //indicacion
        const matlab::data::TypedArray<int32_t> indicacion_arr = arr["indicacion"];
        msg->indicacion = indicacion_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'indicacion' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'indicacion' is wrong type; expected a int32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T hexapod_interfaces_msg_CalcularGoal_common::get_arr(MDFactory_T& factory, const hexapod_interfaces::action::Calcular::Goal* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","indicacion"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("hexapod_interfaces/CalcularGoal");
    // indicacion
    auto currentElement_indicacion = (msg + ctr)->indicacion;
    outArray[ctr]["indicacion"] = factory.createScalar(currentElement_indicacion);
    }
    return std::move(outArray);
  }

class HEXAPOD_INTERFACES_EXPORT hexapod_interfaces_msg_CalcularResult_common : public MATLABROS2MsgInterface<hexapod_interfaces::action::Calcular::Result> {
  public:
    virtual ~hexapod_interfaces_msg_CalcularResult_common(){}
    virtual void copy_from_struct(hexapod_interfaces::action::Calcular::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const hexapod_interfaces::action::Calcular::Result* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void hexapod_interfaces_msg_CalcularResult_common::copy_from_struct(hexapod_interfaces::action::Calcular::Result* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //flag
        const matlab::data::TypedArray<bool> flag_arr = arr["flag"];
        msg->flag = flag_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'flag' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'flag' is wrong type; expected a logical.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T hexapod_interfaces_msg_CalcularResult_common::get_arr(MDFactory_T& factory, const hexapod_interfaces::action::Calcular::Result* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","flag"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("hexapod_interfaces/CalcularResult");
    // flag
    auto currentElement_flag = (msg + ctr)->flag;
    outArray[ctr]["flag"] = factory.createScalar(currentElement_flag);
    }
    return std::move(outArray);
  }

class HEXAPOD_INTERFACES_EXPORT hexapod_interfaces_msg_CalcularFeedback_common : public MATLABROS2MsgInterface<hexapod_interfaces::action::Calcular::Feedback> {
  public:
    virtual ~hexapod_interfaces_msg_CalcularFeedback_common(){}
    virtual void copy_from_struct(hexapod_interfaces::action::Calcular::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const hexapod_interfaces::action::Calcular::Feedback* msg, MultiLibLoader loader, size_t size = 1);
};
  //----------------------------------------------------------------------------
  void hexapod_interfaces_msg_CalcularFeedback_common::copy_from_struct(hexapod_interfaces::action::Calcular::Feedback* msg, const matlab::data::Struct& arr, MultiLibLoader loader) {
    try {
        //position
        const matlab::data::TypedArray<int32_t> position_arr = arr["position"];
        msg->position = position_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'position' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'position' is wrong type; expected a int32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T hexapod_interfaces_msg_CalcularFeedback_common::get_arr(MDFactory_T& factory, const hexapod_interfaces::action::Calcular::Feedback* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","position"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("hexapod_interfaces/CalcularFeedback");
    // position
    auto currentElement_position = (msg + ctr)->position;
    outArray[ctr]["position"] = factory.createScalar(currentElement_position);
    }
    return std::move(outArray);
  }

class HEXAPOD_INTERFACES_EXPORT ros2_hexapod_interfaces_Calcular_action : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_hexapod_interfaces_Calcular_action(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABActClientInterface> generateActClientInterface();
    virtual std::shared_ptr<MATLABActServerInterface> generateActServerInterface();
    virtual matlab::data::StructArray generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap);
    virtual std::shared_ptr<void> generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_hexapod_interfaces_Calcular_action::generatePublisherInterface(ElementType type){
    std::shared_ptr<MATLABPublisherInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2PublisherImpl<hexapod_interfaces::action::Calcular::Goal,hexapod_interfaces_msg_CalcularGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2PublisherImpl<hexapod_interfaces::action::Calcular::Feedback,hexapod_interfaces_msg_CalcularFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2PublisherImpl<hexapod_interfaces::action::Calcular::Result,hexapod_interfaces_msg_CalcularResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_hexapod_interfaces_Calcular_action::generateSubscriberInterface(ElementType type){
    std::shared_ptr<MATLABSubscriberInterface> ptr;
    if(type == eGoal){
        ptr = std::make_shared<ROS2SubscriberImpl<hexapod_interfaces::action::Calcular::Goal,hexapod_interfaces_msg_CalcularGoal_common>>();
    }else if(type == eFeedback){
        ptr = std::make_shared<ROS2SubscriberImpl<hexapod_interfaces::action::Calcular::Feedback,hexapod_interfaces_msg_CalcularFeedback_common>>();
    }else if(type == eResult){
        ptr = std::make_shared<ROS2SubscriberImpl<hexapod_interfaces::action::Calcular::Result,hexapod_interfaces_msg_CalcularResult_common>>();
    }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
    return ptr;
  }
  std::shared_ptr<MATLABActClientInterface> 
          ros2_hexapod_interfaces_Calcular_action::generateActClientInterface(){
      return std::make_shared<ROS2ActClientImpl<hexapod_interfaces::action::Calcular,hexapod_interfaces::action::Calcular::Goal,hexapod_interfaces::action::Calcular::Feedback::ConstSharedPtr,hexapod_interfaces::action::Calcular::Result::ConstSharedPtr,hexapod_interfaces_msg_CalcularGoal_common,hexapod_interfaces_msg_CalcularFeedback_common,hexapod_interfaces_msg_CalcularResult_common>>();
  }
  std::shared_ptr<MATLABActServerInterface> 
          ros2_hexapod_interfaces_Calcular_action::generateActServerInterface(){
      return std::make_shared<ROS2ActServerImpl<hexapod_interfaces::action::Calcular,hexapod_interfaces::action::Calcular::Feedback,hexapod_interfaces::action::Calcular::Result,hexapod_interfaces::action::Calcular::Goal::ConstSharedPtr,hexapod_interfaces_msg_CalcularGoal_common,hexapod_interfaces_msg_CalcularFeedback_common,hexapod_interfaces_msg_CalcularResult_common>>();
  }
  std::shared_ptr<void> ros2_hexapod_interfaces_Calcular_action::generateCppMessage(ElementType type, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
        auto msg = std::make_shared<hexapod_interfaces::action::Calcular::Goal>();
        hexapod_interfaces_msg_CalcularGoal_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eFeedback){
        auto msg = std::make_shared<hexapod_interfaces::action::Calcular::Feedback>();
        hexapod_interfaces_msg_CalcularFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
    }else if(type == eResult){
        auto msg = std::make_shared<hexapod_interfaces::action::Calcular::Result>();
        hexapod_interfaces_msg_CalcularResult_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
        commonObj.copy_from_struct(msg.get(), arr[0], loader);
        return msg;
   }else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
 matlab::data::StructArray ros2_hexapod_interfaces_Calcular_action::generateMLMessage(ElementType type, 
                                                    void*  msgPtr ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    if(type == eGoal){
	    hexapod_interfaces_msg_CalcularGoal_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (hexapod_interfaces::action::Calcular::Goal*)msgPtr, loader);
    }else if(type == eResult){
        hexapod_interfaces_msg_CalcularResult_common commonObj;	
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (hexapod_interfaces::action::Calcular::Result*)msgPtr, loader);
    }else if(type == eFeedback){
        hexapod_interfaces_msg_CalcularFeedback_common commonObj;
        commonObj.mCommonObjMap = commonObjMap;
	    MDFactory_T factory;
	    return commonObj.get_arr(factory, (hexapod_interfaces::action::Calcular::Feedback*)msgPtr, loader);
    }
     else{
        throw std::invalid_argument("Wrong input, Expected 'Goal' or 'Feedback' or 'Result'");
    }
  }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(hexapod_interfaces_msg_CalcularGoal_common, MATLABROS2MsgInterface<hexapod_interfaces::action::Calcular::Goal>)
CLASS_LOADER_REGISTER_CLASS(hexapod_interfaces_msg_CalcularFeedback_common, MATLABROS2MsgInterface<hexapod_interfaces::action::Calcular::Feedback>)
CLASS_LOADER_REGISTER_CLASS(hexapod_interfaces_msg_CalcularResult_common, MATLABROS2MsgInterface<hexapod_interfaces::action::Calcular::Result>)
CLASS_LOADER_REGISTER_CLASS(ros2_hexapod_interfaces_Calcular_action, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1