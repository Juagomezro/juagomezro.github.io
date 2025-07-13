function [data, info] = posicionarFeedback
%PosicionarFeedback gives an empty data for hexapod_interfaces/PosicionarFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/PosicionarFeedback';
[data.status, info.status] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'hexapod_interfaces/PosicionarFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'status';
