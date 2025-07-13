function [data, info] = obtenerObjetosResponse
%ObtenerObjetos gives an empty data for hexapod_interfaces/ObtenerObjetosResponse
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'hexapod_interfaces/ObtenerObjetosResponse';
[data.objetos, info.objetos] = ros.internal.ros2.custommessages.hexapod_interfaces.objeto;
info.objetos.MLdataType = 'struct';
info.objetos.MaxLen = NaN;
info.objetos.MinLen = 0;
info.MessageType = 'hexapod_interfaces/ObtenerObjetosResponse';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,4);
info.MatPath{1} = 'objetos';
info.MatPath{2} = 'objetos.x';
info.MatPath{3} = 'objetos.y';
info.MatPath{4} = 'objetos.color';
