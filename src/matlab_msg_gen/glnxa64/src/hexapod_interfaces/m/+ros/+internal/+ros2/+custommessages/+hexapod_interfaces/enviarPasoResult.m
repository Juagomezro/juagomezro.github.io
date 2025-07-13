function [data, info] = enviarPasoResult
%EnviarPasoResult gives an empty data for hexapod_interfaces/EnviarPasoResult
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/EnviarPasoResult';
[data.recibido, info.recibido] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'hexapod_interfaces/EnviarPasoResult';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'recibido';
