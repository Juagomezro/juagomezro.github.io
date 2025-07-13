function [data, info] = obtenerPoseRobotResponse
%ObtenerPoseRobot gives an empty data for hexapod_interfaces/ObtenerPoseRobotResponse
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/ObtenerPoseRobotResponse';
[data.x, info.x] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.y, info.y] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.angle, info.angle] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
info.MessageType = 'hexapod_interfaces/ObtenerPoseRobotResponse';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'x';
info.MatPath{2} = 'y';
info.MatPath{3} = 'angle';
