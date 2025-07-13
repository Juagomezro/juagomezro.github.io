function [data, info] = mapaDatos
%MapaDatos gives an empty data for vision_node/MapaDatos
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'vision_node/MapaDatos';
[data.matriz, info.matriz] = ros.internal.ros2.messages.ros2.default_type('double',NaN,0);
[data.vector, info.vector] = ros.internal.ros2.messages.ros2.default_type('double',NaN,0);
[data.pose, info.pose] = ros.internal.ros2.messages.ros2.default_type('double',3,0);
info.MessageType = 'vision_node/MapaDatos';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'matriz';
info.MatPath{2} = 'vector';
info.MatPath{3} = 'pose';
