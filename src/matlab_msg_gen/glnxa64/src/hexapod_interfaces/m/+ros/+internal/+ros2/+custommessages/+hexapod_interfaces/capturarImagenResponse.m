function [data, info] = capturarImagenResponse
%CapturarImagen gives an empty data for hexapod_interfaces/CapturarImagenResponse
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/CapturarImagenResponse';
[data.imagen_base64, info.imagen_base64] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'hexapod_interfaces/CapturarImagenResponse';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'imagen_base64';
