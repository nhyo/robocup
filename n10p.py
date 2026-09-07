#---------------CONFIG AREA (most of the time you only need to change here)-------------
ICON = "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" 
UDP_IP = "0.0.0.0"  # Listen on all local network interfaces
UDP_PORT = 8082
TITLE = "N10p Points Cloud"
SKIP_FRAME = 5
FKeys = ['dev','devk','devb','width','l_num','r_num','left_weight','aim','speed']
Colors = [(255, 255, 0),(0, 255, 255),(255, 0, 255)]

#---------------INIT AREA-------------
import socket
import time
import math
import pygame
import threading
import struct
import base64
import datetime
import os
import tkinter as tk
import numpy as np
from io import BytesIO
from tkinter import filedialog

#you should calculate how to draw when change width and height
WIDTH = 800
HEIGHT = 800
CENTER_X = WIDTH // 2
CENTER_Y = HEIGHT // 2
MAX_RADIUS = min(CENTER_X, CENTER_Y)
BLACK = (0, 0, 0)
WHITE = (50, 50, 50)
TRUE_WHITE = (255,255,255)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 8192)
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
font = pygame.font.Font(None, 16)
pygame.display.set_caption(TITLE)

#----------------RECV AND DRAW MAIN DATA-------------
frame_udp = None

data_buffer = b''
def parse_frame_udp():
    global frame_udp,data_buffer
    while True:
        data_buffer += sock.recvfrom(6000)[0]
        while (b'[end]' in data_buffer):
            #read whole datas of a frame
            end_index = data_buffer.find(b'[end]')
            complete_data = data_buffer[:end_index]
            data_buffer = data_buffer[end_index + 5:]
            read_index = 0

            #parse float datas from the frame(float)
            float_datas,read_index = recv_data('f',complete_data,read_index)
            if((float_datas is None) and read_index == -1):continue

            #parse point datas from the frame (N10P_DATA{uint8_t,uint8_t})
            all_point_datas = []
            color_index = 0
            error_flag = False
            while read_index < len(complete_data):
                point_datas,read_index = recv_data('BB',complete_data,read_index)
                if((point_datas is None) and read_index == -1):
                    error_flag = True
                    break
                all_point_datas.append({'Datas':point_datas,'Color':color_index})
                color_index = color_index + 1
            if(error_flag):continue
            frame_udp = {'Fdatas':float_datas,'Pdatas':all_point_datas}

def draw_frame(frame):
    global frame_udp
    #draw float datas on the screen
    for i, f in enumerate(frame['Fdatas']):
        draw_float(FKeys[i],f[0],i)

    #draw point datas on the screen
    for p in frame['Pdatas']:
        color = p['Color']
        for point in p['Datas']:
            x = CENTER_X - (point[0]-128)*2.5
            y = CENTER_Y - (point[1]-128)*2.5
            if(not(math.isnan(x) or math.isnan(y))):
                pygame.draw.circle(screen, Colors[color], (int(x), int(y)), 1)

#----------------SOME BUTTONS ,RECORD&PLAY------------------
recording = False
playing = False
udpOpen = True
frames_to_record = []
button_udp = pygame.Rect(700, 20, 90, 40)
button_recorder = pygame.Rect(700, 70, 90, 40)
button_play = pygame.Rect(700, 120, 90, 40)
def toggle_recording():
    global recording, frames_to_record
    recording = not recording
    if not recording:
        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = os.path.join(os.path.dirname(__file__),f"{timestamp}")
        np.save(filename, frames_to_record)
        if((frames_to_record is not None) and len(frames_to_record)!=0):print(filename+".npy")
        else:print("Error:could not save a empty array")
        frames_to_record = []

def toggle_udp():
    global frames_to_record,recording,udpOpen
    udpOpen = not udpOpen
    if(not udpOpen):
        frames_to_record = []
        recording  = False

play_frames = []
play_index = 0
playFlag = False
def toggle_play():
    global frames_to_record,recording,udpOpen,playing,play_frames,play_index,playFlag
    playing = not playing
    if(playing):
        play_frames = load_frame()
        if(play_frames is None):
            playing = False
    else :
        playFlag = True
        play_frames = []
        play_index = 0

def draw_button(button,word,status):
    pygame.draw.rect(screen, TRUE_WHITE, button)
    if(status):label = font.render(word + " ON", True, (205,51,51))
    else:label = font.render(word + " OFF", True, BLACK)
    screen.blit(label, label.get_rect(center=button.center))

def record_frame():
    frames_to_record.append(frame_udp)

def load_frame():
    global playing,udpOpen
    root = tk.Tk()
    root.withdraw()
    file_path = filedialog.askopenfilename(
        defaultextension=".npy",
        filetypes=[("NumPy arrays", "*.npy")],
        title="选择雷达点云数据文件"
    )
    if file_path:
      try:
          loaded_array = np.load(file_path,allow_pickle=True)
          print("Success read file! " + "[" + file_path + "]")
          return loaded_array
      except Exception as e:
          print("Error: "+ str(e) + " [" + file_path + "]")
          return None
    else:return None

def draw_play_info():
    global play_frames,play_index
    label = font.render("frame:  " + str(play_index+1)+"  /  "+str(len(play_frames)), True, TRUE_WHITE)
    label_rect = label.get_rect(center=(735, 720))
    screen.blit(label, label_rect)

    label = font.render("press A to prev frame", True, TRUE_WHITE)
    label_rect = label.get_rect(center=(735, 740))
    screen.blit(label, label_rect)

    label = font.render("press D to next frame", True, TRUE_WHITE)
    label_rect = label.get_rect(center=(735, 760))
    screen.blit(label, label_rect)

    label = font.render("press SPACE to play  /  stop", True, TRUE_WHITE)
    label_rect = label.get_rect(center=(720, 780))
    screen.blit(label, label_rect)


#----------------NOT IMPORTANT------------------
def recv_data(format,source,index):
    try:
        #read the lengh of  array (uint16_t)
        length = struct.unpack_from('H', source, index)[0]
        index = index + 2

        #read the array (arr)
        datas = []
        for _ in range(length):
            datas.append(struct.unpack_from(format, source, index))
            index = index + struct.calcsize(format)
        return (datas,index)
    except Exception:
        return (None,-1)

def draw_float(key,value,i):
        label = font.render(key+":  "+ str(round(value,2)), True, TRUE_WHITE)
        label_rect = label.get_rect(center=(80, 30+i*20))
        screen.blit(label, label_rect)

def draw_grid():
    for i in range(-8, 9): 
        radius = (i / 8) * MAX_RADIUS
        pygame.draw.circle(screen, WHITE, (CENTER_X, CENTER_Y), abs(radius), 1)

        label = font.render(str(i * 20), True, TRUE_WHITE)
        label_rect = label.get_rect(center=(CENTER_X + radius + 10, CENTER_Y-10))
        screen.blit(label, label_rect)
    for i in range(-8, 9): 
        pygame.draw.line(screen, WHITE, (i * 50 + CENTER_X, CENTER_Y - MAX_RADIUS), (i * 50 + CENTER_X, CENTER_Y + MAX_RADIUS), 1)
        label = font.render(str(-i * 20), True, TRUE_WHITE) 
        label_rect = label.get_rect(center=(CENTER_X - 10, i * 50 + CENTER_Y + 10))
        screen.blit(label, label_rect)
    for i in range(1,16):
        pygame.draw.line(screen, WHITE, (i*50, CENTER_Y - MAX_RADIUS), (i*50, CENTER_Y + MAX_RADIUS), 1)
        pygame.draw.line(screen, WHITE, (CENTER_X - MAX_RADIUS,i*50), (CENTER_X + MAX_RADIUS,i*50), 1)

mouse_x = 0
mouse_y = 0
def draw_signature():
    global mouse_x,mouse_y

    label = font.render("programed by TangSong404", True, TRUE_WHITE)
    label_rect = label.get_rect(center=(90, 780))
    screen.blit(label, label_rect)

    label = font.render("( " + str(int((mouse_x-CENTER_X)/2.5)) + "  ,  "+ str(int((CENTER_Y-mouse_y)/2.5))+ " )", True, TRUE_WHITE)
    label_rect = label.get_rect(center=(50, 760))
    screen.blit(label, label_rect)
    pygame.draw.circle(screen, (0, 255, 0), (int(mouse_x), int(mouse_y)), 1)


#----------------PROGRAM START------------------
icon_data = base64.b64decode(ICON)
icon_bytes = BytesIO(icon_data)
icon = pygame.image.load(icon_bytes)
pygame.display.set_icon(icon)

udp_thread = threading.Thread(target=parse_frame_udp)
udp_thread.daemon = True 
udp_thread.start()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            if button_recorder.collidepoint(event.pos) and udpOpen:toggle_recording()
            elif button_udp.collidepoint(event.pos) and not playing:toggle_udp()
            elif button_play.collidepoint(event.pos) and not udpOpen:toggle_play()
            elif event.button==1: mouse_x, mouse_y = pygame.mouse.get_pos()
            elif event.button==3:
                mouse_x = 0
                mouse_y = 0
        if event.type == pygame.KEYDOWN:
            if (event.unicode=='a' or event.unicode=='A')and playing:play_index = (play_index-SKIP_FRAME + len(play_frames))%len(play_frames)
            elif (event.unicode=='d' or event.unicode=='D')and playing:play_index = (play_index+SKIP_FRAME)%len(play_frames)
            elif event.unicode==' ' and playing:playFlag = not playFlag

    screen.fill(BLACK)
    draw_grid()
    draw_signature()
    draw_button(button_recorder,"RECODER",recording)
    draw_button(button_udp,"UDP",udpOpen)
    draw_button(button_play,"PLAY",playing)

    if((udpOpen and (frame_udp is not None))):
        draw_frame(frame_udp)
        if(recording):record_frame()

    elif((play_frames is not None) and len(play_frames)!=0 and playing):
        draw_frame(play_frames[play_index])
        if(playFlag):play_index = (play_index+1)%len(play_frames)
        draw_play_info()

    pygame.display.flip()
    time.sleep(0.01)

pygame.quit()
