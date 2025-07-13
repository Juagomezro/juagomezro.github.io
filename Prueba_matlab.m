% Inicializar nodo
node = ros2node("/cliente_mapa");

% Crear cliente del servicio
cli = ros2svcclient(node, "/get_mapa_binario", "hexapod_interfaces/CapturarImagen");

% Crear request
req = ros2message(cli);

% Llamar al servicio
resp = call(cli, req, Timeout=5);

% Decodificar base64
img_bytes = matlab.net.base64decode(char(resp.imagen_base64));

% Escribir bytes en archivo temporal
tmpfile = [tempname, '.jpg'];
fid = fopen(tmpfile, 'w');
fwrite(fid, img_bytes, 'uint8');
fclose(fid);

% Leer imagen desde archivo
img = not(imread(tmpfile));

% Mostrar imagen
figure;
imshow(img);
title("Mapa binario (sin flecha y sin marcador)");

% Eliminar archivo temporal
delete(tmpfile);
