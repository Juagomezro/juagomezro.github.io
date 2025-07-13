function [data, info] = obtenerObjetosRequest
%ObtenerObjetos gives an empty data for hexapod_interfaces/ObtenerObjetosRequest
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/ObtenerObjetosRequest';
info.MessageType = 'hexapod_interfaces/ObtenerObjetosRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,0);
