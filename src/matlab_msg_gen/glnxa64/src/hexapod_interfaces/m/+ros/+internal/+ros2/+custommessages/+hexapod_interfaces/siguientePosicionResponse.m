function [data, info] = siguientePosicionResponse
%SiguientePosicion gives an empty data for hexapod_interfaces/SiguientePosicionResponse
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/SiguientePosicionResponse';
[data.positions, info.positions] = ros.internal.ros2.messages.ros2.default_type('single',NaN,0);
info.MessageType = 'hexapod_interfaces/SiguientePosicionResponse';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'positions';
