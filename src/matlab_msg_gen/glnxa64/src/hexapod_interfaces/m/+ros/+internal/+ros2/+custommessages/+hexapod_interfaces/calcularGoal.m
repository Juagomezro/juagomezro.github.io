function [data, info] = calcularGoal
%CalcularGoal gives an empty data for hexapod_interfaces/CalcularGoal
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/CalcularGoal';
[data.indicacion, info.indicacion] = ros.internal.ros2.messages.ros2.default_type('int32',1,0);
info.MessageType = 'hexapod_interfaces/CalcularGoal';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'indicacion';
