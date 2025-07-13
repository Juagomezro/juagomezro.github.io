// Copyright 2020-2022 The MathWorks, Inc.
// Common copy functions for vision_node/MapaDatos
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
#include "vision_node/msg/mapa_datos.hpp"
#include "visibility_control.h"
#include "class_loader/multi_library_class_loader.hpp"
#include "ROS2PubSubTemplates.hpp"
class VISION_NODE_EXPORT ros2_vision_node_msg_MapaDatos_common : public MATLABROS2MsgInterface<vision_node::msg::MapaDatos> {
  public:
    virtual ~ros2_vision_node_msg_MapaDatos_common(){}
    virtual void copy_from_struct(vision_node::msg::MapaDatos* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const vision_node::msg::MapaDatos* msg, MultiLibLoader loader, size_t size = 1);
};
  void ros2_vision_node_msg_MapaDatos_common::copy_from_struct(vision_node::msg::MapaDatos* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //matriz
        const matlab::data::TypedArray<double> matriz_arr = arr["matriz"];
        size_t nelem = matriz_arr.getNumberOfElements();
        	msg->matriz.resize(nelem);
        	std::copy(matriz_arr.begin(), matriz_arr.begin()+nelem, msg->matriz.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'matriz' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'matriz' is wrong type; expected a double.");
    }
    try {
        //vector
        const matlab::data::TypedArray<double> vector_arr = arr["vector"];
        size_t nelem = vector_arr.getNumberOfElements();
        	msg->vector.resize(nelem);
        	std::copy(vector_arr.begin(), vector_arr.begin()+nelem, msg->vector.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'vector' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'vector' is wrong type; expected a double.");
    }
    try {
        //pose
        const matlab::data::TypedArray<double> pose_arr = arr["pose"];
        size_t nelem = 3;
        	std::copy(pose_arr.begin(), pose_arr.begin()+nelem, msg->pose.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'pose' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'pose' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T ros2_vision_node_msg_MapaDatos_common::get_arr(MDFactory_T& factory, const vision_node::msg::MapaDatos* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","matriz","vector","pose"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("vision_node/MapaDatos");
    // matriz
    auto currentElement_matriz = (msg + ctr)->matriz;
    outArray[ctr]["matriz"] = factory.createArray<vision_node::msg::MapaDatos::_matriz_type::const_iterator, double>({currentElement_matriz.size(), 1}, currentElement_matriz.begin(), currentElement_matriz.end());
    // vector
    auto currentElement_vector = (msg + ctr)->vector;
    outArray[ctr]["vector"] = factory.createArray<vision_node::msg::MapaDatos::_vector_type::const_iterator, double>({currentElement_vector.size(), 1}, currentElement_vector.begin(), currentElement_vector.end());
    // pose
    auto currentElement_pose = (msg + ctr)->pose;
    outArray[ctr]["pose"] = factory.createArray<vision_node::msg::MapaDatos::_pose_type::const_iterator, double>({currentElement_pose.size(), 1}, currentElement_pose.begin(), currentElement_pose.end());
    }
    return std::move(outArray);
  } 
class VISION_NODE_EXPORT ros2_vision_node_MapaDatos_message : public ROS2MsgElementInterfaceFactory {
  public:
    virtual ~ros2_vision_node_MapaDatos_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType /*type*/);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType /*type*/);
    virtual std::shared_ptr<void> generateCppMessage(ElementType /*type*/, const matlab::data::StructArray& /* arr */, MultiLibLoader /* loader */, std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
    virtual matlab::data::StructArray generateMLMessage(ElementType  /*type*/ ,void*  /* msg */, MultiLibLoader /* loader */ , std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* /*commonObjMap*/);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          ros2_vision_node_MapaDatos_message::generatePublisherInterface(ElementType /*type*/){
    return std::make_shared<ROS2PublisherImpl<vision_node::msg::MapaDatos,ros2_vision_node_msg_MapaDatos_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         ros2_vision_node_MapaDatos_message::generateSubscriberInterface(ElementType /*type*/){
    return std::make_shared<ROS2SubscriberImpl<vision_node::msg::MapaDatos,ros2_vision_node_msg_MapaDatos_common>>();
  }
  std::shared_ptr<void> ros2_vision_node_MapaDatos_message::generateCppMessage(ElementType /*type*/, 
                                           const matlab::data::StructArray& arr,
                                           MultiLibLoader loader,
                                           std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>* commonObjMap){
    auto msg = std::make_shared<vision_node::msg::MapaDatos>();
    ros2_vision_node_msg_MapaDatos_common commonObj;
    commonObj.mCommonObjMap = commonObjMap;
    commonObj.copy_from_struct(msg.get(), arr[0], loader);
    return msg;
  }
  matlab::data::StructArray ros2_vision_node_MapaDatos_message::generateMLMessage(ElementType  /*type*/ ,
                                                    void*  msg ,
                                                    MultiLibLoader  loader ,
                                                    std::map<std::string,std::shared_ptr<MATLABROS2MsgInterfaceBase>>*  commonObjMap ){
    ros2_vision_node_msg_MapaDatos_common commonObj;	
    commonObj.mCommonObjMap = commonObjMap;	
    MDFactory_T factory;
    return commonObj.get_arr(factory, (vision_node::msg::MapaDatos*)msg, loader);			
 }
#include "class_loader/register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(ros2_vision_node_msg_MapaDatos_common, MATLABROS2MsgInterface<vision_node::msg::MapaDatos>)
CLASS_LOADER_REGISTER_CLASS(ros2_vision_node_MapaDatos_message, ROS2MsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER