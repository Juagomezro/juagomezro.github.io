function [data, info] = posicionarGoal
%PosicionarGoal gives an empty data for hexapod_interfaces/PosicionarGoal
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/PosicionarGoal';
[data.positions, info.positions] = ros.internal.ros2.messages.ros2.default_type('int32',NaN,0);
info.MessageType = 'hexapod_interfaces/PosicionarGoal';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'positions';
