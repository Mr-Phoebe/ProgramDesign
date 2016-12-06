function varargout = pic_editor(varargin)
% PIC_EDITOR M-file for pic_editor.fig
%      PIC_EDITOR, by itself, creates a new PIC_EDITOR or raises the existing
%      singleton*.
% 
%      H = PIC_EDITOR returns the handle to a new PIC_EDITOR or the handle to
%      the existing singleton*.
%
%      PIC_EDITOR('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PIC_EDITOR.M with the given input arguments.
%
%      PIC_EDITOR('Property','Value',...) creates a new PIC_EDITOR or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before pic_editor_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to pic_editor_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help pic_editor

% Last Modified by GUIDE v2.5 06-Dec-2016 10:35:43

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @pic_editor_OpeningFcn, ...
                   'gui_OutputFcn',  @pic_editor_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before pic_editor is made visible.
function pic_editor_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to pic_editor (see VARARGIN)

% Set the name for GUI
set(gcf,'numbertitle','off','name','untitiled1');

% Choose default command line output for pic_editor
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes pic_editor wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = pic_editor_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --------------------------------------------------------------------
function menu_file_Callback(hObject, eventdata, handles)
% hObject    handle to menu_file (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function menu_edit_Callback(hObject, eventdata, handles)
% hObject    handle to menu_edit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function menu_noise_Callback(hObject, eventdata, handles)
% hObject    handle to menu_noise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function edit_rgb2gry_Callback(hObject, eventdata, handles)
% hObject    handle to edit_rgb2gry (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %彩色图像转为灰色图像
global A
axes(handles.axes2);
imsize = size(image);
if numel(imsize) > 2
    imshow(rgb2gray(image));
else
    msgbox('error');
end




% --------------------------------------------------------------------
function file_open_Callback(hObject, eventdata, handles)
% hObject    handle to file_open (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %打开图片
global A
[filename,pathname]=...
    uigetfile({'*.jpg';'*.bap';'*.gif'},'选择图片');
str=[pathname,filename];
image=imread(str);
A=str;
axes(handles.axes1);
imshow(image);


% --------------------------------------------------------------------
function file_save_as_Callback(hObject, eventdata, handles)
% hObject    handle to file_save_as (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --------------------------------------------------------------------
function file_exit_Callback(hObject, eventdata, handles)
% hObject    handle to file_exit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(gcf)  %退出


% --------------------------------------------------------------------
function noise_salt_pepper_Callback(hObject, eventdata, handles)
% hObject    handle to noise_salt_pepper (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %加椒盐噪声
global A
axes(handles.axes2);
a=imnoise(image,'salt & pepper',0.02);
imshow(a);

% --------------------------------------------------------------------
function noise_gaussian_Callback(hObject, eventdata, handles)
% hObject    handle to noise_gaussian (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image    %加高斯噪声
global A
axes(handles.axes3);
a=imnoise(image,'gaussian',0.02);
imshow(a);


% --------------------------------------------------------------------
function menu_smoothing_Callback(hObject, eventdata, handles)
% hObject    handle to menu_smoothing (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function smoothing_average_Callback(hObject, eventdata, handles)
% hObject    handle to smoothing_average (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %均值滤波
global A
h=fspecial('average',5);
g=imfilter(image,h);
axes(handles.axes2);
imshow(g);


% --------------------------------------------------------------------
function smoothing_gaussian_Callback(hObject, eventdata, handles)
% hObject    handle to smoothing_gaussian (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %高斯低通滤波
global A
h=fspecial('gaussian',9);
g=imfilter(image,h);
axes(handles.axes3);
imshow(g);

% --------------------------------------------------------------------
function sharpen_laplacian_Callback(hObject, eventdata, handles)
% hObject    handle to sharpen_laplacian (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %拉布拉斯锐化算子
global A
h=fspecial('laplacian',0.5);
g=imfilter(image,h);
axes(handles.axes2);
imshow(g);


% --------------------------------------------------------------------
function smoothing_motion_Callback(hObject, eventdata, handles)
% hObject    handle to smoothing_motion (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  
global A
h=fspecial('motion',20);
g=imfilter(image,h);
axes(handles.axes2);
imshow(g);


% --------------------------------------------------------------------
function smoothing_unsharp_Callback(hObject, eventdata, handles)
% hObject    handle to smoothing_unsharp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %对比度增强滤波
global A
h=fspecial('unsharp',0.5);
g=imfilter(image,h);
axes(handles.axes2);
imshow(g);


% --------------------------------------------------------------------
function menu_edge_Callback(hObject, eventdata, handles)
% hObject    handle to menu_edge (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function edge_sobel_Callback(hObject, eventdata, handles)
% hObject    handle to edge_sobel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %sobel边缘检测
global A
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
else
    a=image;
end
axes(handles.axes2);
b=edge(a,'sobel');
imshow(b);


% --------------------------------------------------------------------
function edge_prewitt_Callback(hObject, eventdata, handles)
% hObject    handle to edge_prewitt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image    %prewitt边缘检测
global A
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
else
    a=image;
end
axes(handles.axes3);
b=edge(a,'prewitt');
imshow(b);


% --------------------------------------------------------------------
function edge_canny_Callback(hObject, eventdata, handles)
% hObject    handle to edge_canny (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image    %canny边缘检测
global A
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
else
    a=image;
end
axes(handles.axes4);
b=edge(a,'canny');
imshow(b);


% --------------------------------------------------------------------
function menu_zoom_Callback(hObject, eventdata, handles)
% hObject    handle to menu_zoom (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function zoom_nearest_Callback(hObject, eventdata, handles)
% hObject    handle to zoom_nearest (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image    %最近邻插值法
prompt={'请输入参数：'};
defans={'1'};
answer=inputdlg(prompt,'缩放倍数',1,defans,'on');
a=cell2mat(answer);
num=str2num(a);
b=imresize(image,num,'nearest');
axes(handles.axes2);
imshow(b);



% --------------------------------------------------------------------
function zoom_bilinear_Callback(hObject, eventdata, handles)
% hObject    handle to zoom_bilinear (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image    %双线性插值法
prompt={'请输入参数：'};
defans={'1'};
answer=inputdlg(prompt,'缩放倍数',1,defans,'on');
a=cell2mat(answer);
num=str2num(a);
b=imresize(image,num,'bilinear');
axes(handles.axes3);
imshow(b);

% --------------------------------------------------------------------
function zoom_bicubic_Callback(hObject, eventdata, handles)
% hObject    handle to zoom_bicubic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %三次插值法
prompt={'请输入参数:'};
defans={'1'};
answer=inputdlg(prompt,'缩放倍数',1,defans,'on');
a=cell2mat(answer);
num=str2num(a);
b=imresize(image,num,'bicubic');
axes(handles.axes4);
imshow(b);


% --------------------------------------------------------------------
function edit_rotate_Callback(hObject, eventdata, handles)
% hObject    handle to edit_rotate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image    %任意角度旋转
prompt={'请输入角度：'};
defans={'45'};
answer=inputdlg(prompt,'旋转角度',1,defans,'on');
a=cell2mat(answer);
b=str2num(a);
c=imrotate(image,b);
axes(handles.axes2);
imshow(c);


% --------------------------------------------------------------------
function edit_cute_Callback(hObject, eventdata, handles)
% hObject    handle to edit_cute (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %截图并保存图片
a=imcrop(image);
axes(handles.axes2);
imshow(a);
[sfilename sfilepath]=uiputfile({'*.jpg';'*.bap';'*.gif'},'另存为');
image1=[sfilepath,sfilename];
imwrite(a,image1);



% --------------------------------------------------------------------
function apply_invert_Callback(hObject, eventdata, handles)
% hObject    handle to apply_invert (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  % 底片效果
global A
axes(handles.axes2);
y=imadjust(image,[0 1],[1 0]); imshow(y);


% --------------------------------------------------------------------
function edit_histogram1_Callback(hObject, eventdata, handles)
% hObject    handle to edit_histogram1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %原始图片直方图
axes(handles.axes3);
imsize = size(image);
if numel(imsize) > 2
   imhist(rgb2gray(image));
else
   imhist(image);
end


% --------------------------------------------------------------------
function enhancement_histogram_Callback(hObject, eventdata, handles)
% hObject    handle to enhancement_histogram (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %均衡化处理
global A
axes(handles.axes2);
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
    b=histeq(a);
    imshow(b);
else
    b=histeq(image);
    imshow(b);
end


% --------------------------------------------------------------------
function edit_histogram3_Callback(hObject, eventdata, handles)
% hObject    handle to edit_histogram3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %均衡化直方图
axes(handles.axes4);
imsize = size(image);
if numel(image) > 2
    a=rgb2gray(image);
    b=histeq(a);
    imhist(b);
else
    b=histeq(image);
    imhist(b);
end


% --------------------------------------------------------------------
function menu_background_Callback(hObject, eventdata, handles)
% hObject    handle to menu_background (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



% --------------------------------------------------------------------
function menu_type_Callback(hObject, eventdata, handles)
% hObject    handle to menu_type (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --------------------------------------------------------------------
function type_bw_Callback(hObject, eventdata, handles)
% hObject    handle to type_bw (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %转为黑白图像
global A
a=im2bw(image);
axes(handles.axes2);
imshow(a);


% --------------------------------------------------------------------
function type_gray_Callback(hObject, eventdata, handles)
% hObject    handle to type_gray (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image
global A
axes(handles.axes2);
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
    imshow(a);
else
    msgbox('error');
end


% --------------------------------------------------------------------
function background_add_Callback(hObject, eventdata, handles)
% hObject    handle to background_add (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename,pathname]=...
    uigetfile({'*.jpg';'*.bap';'*.gif'},'选择背景图片'); %添加背景图片
str=[pathname,filename];
background=imread(str);
axes(handles.axes5);
imshow(background);

% --------------------------------------------------------------------
function background_clear_Callback(hObject, eventdata, handles)
% hObject    handle to background_clear (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
cla(handles.axes5);   %清除背景图片
clear;


% --------------------------------------------------------------------
function noise_speckle_Callback(hObject, eventdata, handles)
% hObject    handle to noise_speckle (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %加乘法噪声
global A
axes(handles.axes4);
a=imnoise(image,'speckle',0.02);
imshow(a);


% --------------------------------------------------------------------
function type_index_Callback(hObject, eventdata, handles)
% hObject    handle to type_index (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image;  %转为索引图像
global A
axes(handles.axes2);
imsize = size(image);
if numel(imsize) > 2
    [a,map]=rgb2ind(image,16);
    imshow(a,map);
elseif isgray(image)
    [a,map]=gray2ind(image,16);
    imshow(a,map);
else
    msgbox('error');
end


% --------------------------------------------------------------------
function file_close_Callback(hObject, eventdata, handles)
% hObject    handle to file_close (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
cla(handles.axes1);   %关闭所有axes的图片
cla(handles.axes2);
cla(handles.axes3);
cla(handles.axes4);
clear;


% --------------------------------------------------------------------
function menu_histogram_Callback(hObject, eventdata, handles)
% hObject    handle to menu_histogram (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function histogram_1_Callback(hObject, eventdata, handles)
% hObject    handle to histogram_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   % 原始直方图
axes(handles.axes3);
imsize = size(image);
if numel(imsize) > 2
   imhist(rgb2gray(image));
else
   imhist(image);
end

% --------------------------------------------------------------------
function histogram_2_Callback(hObject, eventdata, handles)
% hObject    handle to histogram_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   % 均衡直方图
axes(handles.axes4);
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
    b=histeq(a);
    imhist(b);
else
    b=histeq(image);
    imhist(b);
end

% --------------------------------------------------------------------
function Untitled_frequency_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_frequency (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --------------------------------------------------------------------
function frequency_FFT_Callback(hObject, eventdata, handles)
% hObject    handle to frequency_FFT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image    %FFT变换
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
else 
    a=image;
end
b=fft2(a);
c=fftshift(b);
axes(handles.axes3);
y=log(abs(c(:,:,:)));
imshow(y,[]);
    
% --------------------------------------------------------------------
function frequency_DCT_Callback(hObject, eventdata, handles)
% hObject    handle to frequency_DCT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %DCT变换
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
else 
    a=image;
end
b=dct2(a);
axes(handles.axes4);
y=log(abs(b(:,:,:)));
imshow(y,[]);

% --------------------------------------------------------------------
function frequency_IFFT_Callback(hObject, eventdata, handles)
% hObject    handle to frequency_IFFT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %FFT逆变换
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);  
else 
    a=image;
end
    b=fft2(a);
    c=ifft2(b);
axes(handles.axes2);
imshow(c,[]);


% --------------------------------------------------------------------
function Untitled_IDCT_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_IDCT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %DCT逆变换
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
else 
    a=image;
end
b=dct2(a);
c=idct2(b);
axes(handles.axes2);
imshow(c,[]);


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %亮度调整
a=get(hObject,'Value');
c=imadjust(image,[0.001 1.0],[0,a]);
set(handles.display1,'string',num2str(a));
axes(handles.axes2);
imshow(c);


% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %对比度调整
a=get(hObject,'Value');
c=imadjust(image,[0.001  a],[]);
set(handles.display2,'string',num2str(a));
axes(handles.axes2);
imshow(c);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider5_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider6_Callback(hObject, eventdata, handles)
% hObject    handle to slider6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --------------------------------------------------------------------
function menu_model_Callback(hObject, eventdata, handles)
% hObject    handle to menu_model (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function model_RGB2HSV_Callback(hObject, eventdata, handles)
% hObject    handle to model_RGB2HSV (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %颜色模型转换RGB->HSV
global A
axes(handles.axes2);
imsize = size(image);
if numel(imsize) > 2
   a=rgb2hsv(image);
   imshow(a);
else
    msgbox('it is not a colorized image');
end

% --------------------------------------------------------------------
function model_RGB2NTSC_Callback(hObject, eventdata, handles)
% hObject    handle to model_RGB2NTSC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %颜色模型转换RGB->NTSC
global A
axes(handles.axes3);
imsize = size(image);
if numel(imsize) > 2
   a=rgb2ntsc(image);
   imshow(a);
else
    msgbox('it is not a colorized image');
end


% --------------------------------------------------------------------
function model_RGB2YCBCR_Callback(hObject, eventdata, handles)
% hObject    handle to model_RGB2YCBCR (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %颜色模型转换RGB->YCBCR
global A
axes(handles.axes4);
imsize = size(image);
if numel(imsize) > 2
   a=rgb2ycbcr(image);
   imshow(a);
else
    msgbox('it is not a colorized image');
end


% --------------------------------------------------------------------
function menu_applu_Callback(hObject, eventdata, handles)
% hObject    handle to menu_applu (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function apply_rim_Callback(hObject, eventdata, handles)
% hObject    handle to apply_rim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image     % 添加边框
global A
t1=image;
imsize = size(t1);
if numel(imsize) > 2
[filename, pathname] = uigetfile({'*.bmp';'*.jpg';'*.jpeg'},'Pick an image-file');
y=imread(filename);
T=[0.8 0 0;0 0.8 0;0 0 1];
tform=maketform('affine',T);
g=imtransform(t1,tform);
[M,N,C]=size(g);
    for m=1:256
         for n=1:256
             for c=1:3
               if (m>=26)&(n>=26)&(m<=230)&(n<=230)
                  t1(m,n,c)=g(m-25,n-25,c);
               else
                  t1(m,n,c)=y(m,n,c);
                end
             end 
         end
    end
axes(handles.axes2);
imshow(t1);   
else
    msgbox('it is not a colorized image');
end
 


% --------------------------------------------------------------------
function Untitled_2_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function swelling_Callback(hObject, eventdata, handles)
% hObject    handle to swelling (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  % 膨胀
global A
a=im2bw(image);
b=[0 1 0;1 1 1;0 1 0];
c=imdilate(a,b);
axes(handles.axes3);
imshow(c);


% --------------------------------------------------------------------
function corrosion_Callback(hObject, eventdata, handles)
% hObject    handle to corrosion (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   % 腐蚀
global A
a=im2bw(image);
b=strel('disk',1);
c=imerode(a,b);
axes(handles.axes4);
imshow(c);


% --------------------------------------------------------------------
function ope_open_Callback(hObject, eventdata, handles)
% hObject    handle to ope_open (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   % 开运算
global A
a=im2bw(image);
b=strel('square',2);
c=imopen(a,b);
axes(handles.axes4);
imshow(c);
% --------------------------------------------------------------------
function ope_close_Callback(hObject, eventdata, handles)
% hObject    handle to ope_close (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   % 闭运算
global A
a=im2bw(image);
b=strel('square',2);
c=imclose(a,b);
axes(handles.axes3);
imshow(c);


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image
zoom on

% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image
zoom off

% --- Executes on button press in pushbutton8.
function pushbutton8_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image
zoom out



% --------------------------------------------------------------------
function save_axes2_Callback(hObject, eventdata, handles)
% hObject    handle to save_axes2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image     %对axes2图片进行另存为
[filename,pathname]=uiputfile({'*.jpg';'*.bap';'*.gif'},'保存图片');
if ~isequal(filename,0)
    str = [pathname filename];
    I=getframe(handles.axes2);           
    imwrite(I.cdata,fullfile(pathname,filename))
else
    disp('保存失败');
end;

% --------------------------------------------------------------------
function save_axes3_Callback(hObject, eventdata, handles)
% hObject    handle to save_axes3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image      %对axes3图片进行另存为
[filename,pathname]=uiputfile({'*.jpg';'*.bap';'*.gif'},'保存图片');
if ~isequal(filename,0)
    str = [pathname filename];
    I=getframe(handles.axes3);           
    imwrite(I.cdata,fullfile(pathname,filename))
else
    disp('保存失败');
end;

% --------------------------------------------------------------------
function save_axes4_Callback(hObject, eventdata, handles)
% hObject    handle to save_axes4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image     %对axes4图片进行另存为
[filename,pathname]=uiputfile({'*.jpg';'*.bap';'*.gif'},'保存图片');
if ~isequal(filename,0)
    str = [pathname filename];
    I=getframe(handles.axes4);           
    imwrite(I.cdata,fullfile(pathname,filename))
else
    disp('保存失败');
end;


% --- Executes on button press in pushbutton11.
function pushbutton11_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global A   %还原axes2的图片为原始图片
axes(handles.axes2);
y=imread(A);
imshow(y);


% --- Executes on button press in pushbutton12.
function pushbutton12_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global A     %还原axes3的图片为原始图片
axes(handles.axes3);
y=imread(A);
imshow(y);


% --------------------------------------------------------------------
function edit_mirror_Callback(hObject, eventdata, handles)
% hObject    handle to edit_mirror (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function udmirror_Callback(hObject, eventdata, handles)
% hObject    handle to udmirror (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  % 上下镜像
global A
imsize = size(image);
if numel(imsize) > 2
    for k=1:3
        y(:,:,k)=flipud(image(:,:,k));
    end
else
    y=flipud(image);
end
axes(handles.axes3);
imshow(y);

% --------------------------------------------------------------------
function lrmirror_Callback(hObject, eventdata, handles)
% hObject    handle to lrmirror (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   % 左右镜像
global A
imsize = size(image);
if numel(imsize) > 2
    for k=1:3
        y(:,:,k)=fliplr(image(:,:,k));
    end
else
    y=fliplr(image);
end
axes(handles.axes2);
imshow(y);


% --- Executes on button press in pushbutton13.
function pushbutton13_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global A   %还原axes3的图片为原始图片
axes(handles.axes4);
y=imread(A);
imshow(y);

% --------------------------------------------------------------------
function menu_enhancement_Callback(hObject, eventdata, handles)
% hObject    handle to menu_enhancement (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function enhancement_smoothing_Callback(hObject, eventdata, handles)
% hObject    handle to enhancement_smoothing (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function smoothing_medfilt_Callback(hObject, eventdata, handles)
% hObject    handle to smoothing_medfilt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image  %中值滤波
global A
imsize = size(image);
if numel(imsize) > 2
    a=rgb2gray(image);
else
    a=image;
end
b=medfilt2(a);
axes(handles.axes4);
imshow(b);


% --------------------------------------------------------------------
function enhancement_sharpen_Callback(hObject, eventdata, handles)
% hObject    handle to enhancement_sharpen (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function apply_emboss_Callback(hObject, eventdata, handles)
% hObject    handle to apply_emboss (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %浮雕效果
global A
imsize = size(image);
if numel(imsize) > 2
r=image(:,:,1);
g=image(:,:,2);
b=image(:,:,3);
m = size(image,1);
n = size(image,2);
    for i=3:m-2                                 
        for j=3:n-2
            rr(i,j)=0.25*r(i-1,j-1)+0.25*r(i-2,j-2)+0.25*r(i,j)+0.25*r(i+1,j+1)-1.0*r(i+2,j+2)+128;  
            gg(i,j)=0.25*r(i-1,j-1)+0.25*g(i-2,j-2)+0.25*g(i,j)+0.25*g(i+1,j+1)-1.0*g(i+2,j+2)+128;
            bb(i,j)=0.25*b(i-1,j-1)+0.25*b(i-2,j-2)+0.25*b(i,j)+0.25*b(i+1,j+1)-1.0*b(i+2,j+2)+128;
        end
    end
   
Y(:,:,1)=rr;
Y(:,:,2)=gg;
Y(:,:,3)=bb;
axes(handles.axes2);
imshow(Y);
else
    msgbox('it is not a colorized image');
end
 
    


% --------------------------------------------------------------------
function apply_fog_Callback(hObject, eventdata, handles)
% hObject    handle to apply_fog (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   % 雾化效果
global A
imsize = size(image);
if numel(imsize) > 2
m=size(image,1);
n=size(image,2);
r=image(:,:,1);
g=image(:,:,2);
b=image(:,:,3);
for i=2:m-10          
    for j=2:n-10
        k=rand(1)*10;  %产生一个随机数作为半径

        di=i+round(mod(k,33)); %得到随机横坐标

        dj=j+round(mod(k,33));%得到随机纵坐标
        rr(i,j)=r(di,dj); %将原像素点用随机像素点代替

        gg(i,j)=g(di,dj);
        bb(i,j)=b(di,dj);
    end
end
Y(:,:,1)=rr;
Y(:,:,2)=gg;
Y(:,:,3)=bb;
axes(handles.axes2);
imshow(Y);
else
    msgbox('it is not a colorized image');
end


% --------------------------------------------------------------------
function Untitled_3_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global image   %倒影效果
global A 
imsize = size(image);
if numel(imsize) > 2
m=size(image,1);
n=size(image,2);
img_up=imresize(image,[floor(m*0.5),n]); %将原图像压缩为原来大小的一半
img_down=imrotate(image,180);%压缩后的图像旋转180度
r=img_down(:,:,1);
g=img_down(:,:,2);
b=img_down(:,:,3);
for i=1:m
    for j=1:n              %下半部分图像做左右镜像

        rr(i,n-j+1)=r(i,j);
        gg(i,n-j+1)=g(i,j);
        bb(i,n-j+1)=b(i,j);
    end
end
 Y(:,:,1)=rr;
 Y(:,:,2)=gg;
 Y(:,:,3)=bb;  %Y是镜像以后的图像
img_down=Y;
%*************倒影部分进行雾化，实现更好的倒影效果***********

m1=size(img_down,1);
n1=size(img_down,2);
r1=img_down(:,:,1);
g1=img_down(:,:,2);
b1=img_down(:,:,3);
for i=2:m1-10          
    for j=2:n1-10
        k=rand(1)*10;
        di=i+round(mod(k,33));
        dj=j+round(mod(k,33));
        rr1(i,j)=r1(di,dj);
        gg1(i,j)=g1(di,dj);
        bb1(i,j)=b1(di,dj);
    end
end
Y1(:,:,1)=rr1;
Y1(:,:,2)=gg1;
Y1(:,:,3)=bb1;
%****************雾化完成*******************************
img_down=imresize(Y1,[floor(m*0.5),n]);
Y=[img_up;img_down];
axes(handles.axes2);
imshow(Y)
else
    msgbox('it is not a colorized image');
end


% --------------------------------------------------------------------
function apply_mosaic_Callback(hObject, eventdata, handles)
% hObject    handle to apply_mosaic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
pix_grp = 5;
global image
t=image;
global A
height = size(t,1);
width = size(t,2);
mosaic = imresize(t,[floor(height/pix_grp) floor(width/pix_grp)]);
%B = imresize(A, [numrows numcols]) 将图像A放大，numrows和numcols分别指定目标图像的高度和宽度
mosaic = imresize(mosaic,[height width],'nearest');
axes(handles.axes2);
t=mosaic;
imshow(t);


% --- Executes during object deletion, before destroying properties.
function axes1_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
