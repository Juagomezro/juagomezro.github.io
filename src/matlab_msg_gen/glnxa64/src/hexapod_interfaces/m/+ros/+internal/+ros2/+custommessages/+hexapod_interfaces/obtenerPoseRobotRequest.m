function [data, info] = obtenerPoseRobotRequest
%ObtenerPoseRobot gives an empty data for hexapod_interfaces/ObtenerPoseRobotRequest
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/ObtenerPoseRobotRequest';
info.MessageType = 'hexapod_interfaces/ObtenerPoseRobotRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,0);
