import json
import cv2
import numpy as np
import sys
import random
import os
class VideoDataAugmentation:
    def __init__(self, videos= None, labels = None, angle=15, scale=1.0, frames_variation_prob=0.7,frames_variation_add =2.0,brightness_variation=45, crop_pixels=20, trans_range = 5):
        self.angle = angle
        self.videos = videos
        self.video = None
        self.scale = scale
        self.frames_variation_add = frames_variation_add
        self.frames_variation_prob = frames_variation_prob
        self.labels = labels
        self.brightness_variation = brightness_variation
        self.cols = 0
        self.rows = 0
        self.depth = 0
        self.crop_pixels = crop_pixels
        self.trans_range = trans_range
        
        self.OPERATIONS_PROB = 0.1
        self.FRAMES_DUPLICATE_PROB = frames_variation_prob
        self.FRAMES_DUPLICATED = frames_variation_add
    #Rotate frames of video
    def rotate(self):
        rotation = random.randint(-self.angle, self.angle)
        M = cv2.getRotationMatrix2D((self.cols/2,self.rows/2), rotation,1.0)
        new_video = []
        for image in self.video:
            image = cv2.warpAffine(image, M, (self.cols,self.rows))
            new_video.append(image)

        self.video = new_video
    #https://github.com/vxy10/ImageAugmentation
    def translate(self):
        tr_x = self.trans_range * np.random.uniform()- self.trans_range/2
        tr_y = self.trans_range * np.random.uniform()- self.trans_range/2
        Trans_M = np.float32([[1,0,tr_x],[0,1,tr_y]])
        new_video = []
        for image in self.video:
            
            image = cv2.warpAffine(image, Trans_M, (self.cols, self.rows))
            new_video.append(image)
        self.video = new_video
    #Flip vertical frames of video
    def flip_vertical(self):
        new_video = []
        for image in self.video:
            image = cv2.flip(image, flipCode=0)
            new_video.append(image)
        self.video = new_video
    #Flip horizontal frames of video    
    def flip_horizontal(self):
        new_video = []
        for image in self.video:
            image = cv2.flip(image, flipCode=1)
            new_video.append(image)
        self.video = new_video
    
    def crop(self):
        cols_crop_pix = round(self.crop_pixels*self.cols/self.rows)
        row_crop_pix = int(np.floor(2*random.uniform(0,1)*self.crop_pixels))
        cols_crop_pix = int(np.floor(2*random.uniform(0,1)* cols_crop_pix).astype(int))
        new_video = []
        for image in self.video:
            image = image[row_crop_pix:self.rows - row_crop_pix, cols_crop_pix:self.cols - cols_crop_pix]
            new_video.append(image)
        
        self.cols = new_video[0].shape[1]
        self.rows = new_video[0].shape[0]

        self.video = new_video

    #Add consecutive frames
    def duplicate_frames(self):
        new_video = self.video
        new_labels = self.labels
        finished = False
        frames = [random.uniform(0,1) for _ in xrange(len(new_video))]        
        i = 0
        j = 0
        while not finished:            
            if frames[j] < self.FRAMES_DUPLICATE_PROB:
                new_frames = random.randint(0, self.FRAMES_DUPLICATED)
                              
                j += 1
                for frame in xrange(new_frames):
                    new_video.insert(i,new_video[i])
                    i+=1
            else:
                i+=1
            if(i >= len(new_video) or j >= len(frames)):
                finished = True

        self.video = new_video
        
    def change_brightness(self):
        new_video = []
        value_brightness = random.randint(-100,+100)
        for image in self.video:
            hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
            h,s,v = cv2.split(hsv)
            v = cv2.add(v, value_brightness)
            v[v>255] = 255
            v[v<0] = 0
            final_hsv = cv2.merge((h,s,v))
            image = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2BGR)
            '''cv2.add(hsv[:,:,2], value_brightness, hsv[:,:,2])
            image = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)'''
            new_video.append(image)
        self.video = new_video
        pass
    def add_noise(self):
        new_video = []
        for image in self.video:
            gauss = np.random.normal(0,1, (self.rows,self.cols,self.depth))
            gauss = gauss.reshape(self.rows,self.cols,self.depth).astype('uint8') 
            image = image + gauss       
            #image = cv2.add(image, gauss)
            new_video.append(image)
        self.video = new_video

    def add_blur(self):
        new_video = []
        for image in self.video:
            image = cv2.GaussianBlur(image, (5,5),0)
            new_video.append(image)
        self.video = new_video

    def augmentate(self, scale=2):
        total_videos = len(self.videos) * scale
        i = 0
        new_videos = []
        new_labels = []
        
        functions = [self.add_noise,self.rotate, self.flip_horizontal ,self.change_brightness,self.crop,self.translate, self.add_blur,self.duplicate_frames]#,  self.flip_horizontal, self.crop, self.duplicate_frames, self.change_brightness,self.add_noise,self.add_blur]
        #Iterate the list of list of videos(each element are videos from same video and size)
        for i_video_list in xrange(len(self.videos)):
            
            #Iterate all videos extracted from same video
            for i_video in xrange(len(self.videos[i_video_list])):      
                
                for j in xrange(int(scale)):
                    self.cols = self.videos[i_video_list][i_video][0].shape[1]
                    self.rows = self.videos[i_video_list][i_video][0].shape[0]
                    self.depth = self.videos[i_video_list][i_video][0].shape[2]

                    self.video = self.videos[i_video_list][i_video]
                    
                    random.shuffle(functions)
                    randnums = [random.uniform(0,1) for _ in xrange(len(functions))]
                    
                    for op in xrange(len(functions)):
                        if randnums[op] > self.OPERATIONS_PROB:
                            operation = functions[op]
                            operation()

                    new_videos.append(self.video)
                    new_labels.append(self.labels[i_video_list][i_video])
        return new_videos, new_labels



class PreprocessVideos:
    def __init__(self):
        self.labels_dic = dict()
        self.total_labels = 0
        self.frame_per_frame_labels = None
        self.data_augmentation = None
        self.videos = None
        self.labels = []
        
    def load_data(self, videos_images_folders_path, json_folder_path):        
        self.videos = []
        images = []
        json_videos_data = []
        for directory in os.listdir(videos_images_folders_path):
            sub_dir_path = videos_images_folders_path + '/' + directory
            print("JSON file:" +  sub_dir_path)
            if(os.path.isdir(sub_dir_path)):
                images = []
                for filename in os.listdir(sub_dir_path):
                    print("Files loaded " + filename)
                    img = cv2.imread(os.path.join(sub_dir_path, filename))
                    if img is not None:
                        images.append(np.float32(img))
                    else:
                        print "Cannot open image file with path: " + sub_dir_path+"/"+filename
                        return None
                json_data = self.load_json(json_folder_path+"/"+os.path.basename(sub_dir_path)+".json")
                if(json_data != None):                
                    self.videos.append(images)
                    json_videos_data.append(json_data)
            else:
                print("Videos path is not a folder!")
        self.labels_dic,self.frame_per_frame_labels = self.convert_2_list(json_videos_data)
        self.videos, self.labels = self.frames_2_videos(self.videos,self.frame_per_frame_labels)
        return self.videos, self.labels
    ##Extract json file. Return labels array and frame_per_frame_labels
    def convert_2_list(self,json_videos_data):
        self.labels_dic = {}
        total_frame_per_frame_labels = []
        
        for i in xrange(len(json_videos_data)):
            json_video_data = json_videos_data[i]

            video_labels = json_video_data["all"]
            self.labels.extend(video_labels)
            for j in xrange(len(video_labels)):
                #Video labels of one video
                video_label = video_labels[j]
                try:
                    if self.labels_dic[video_label] != None:
                        
                        video_labels[j] = self.labels_dic[video_label]
                except KeyError:
                    
                    self.labels_dic[video_label] = self.total_labels
                    video_labels[j] = self.total_labels
                    self.total_labels += 1
                    
            video_actions = json_video_data["sequence"]["actions"]
            video_frame_per_frame_labels = []
            
            for frame in video_actions:
                try:                            
                    if frame != -1:
                        key = video_labels[frame]
                    else:
                        key = -1
                    video_frame_per_frame_labels.append(key)
                    
                except KeyError:
                    pass
            total_frame_per_frame_labels.append(video_frame_per_frame_labels)
        return self.labels_dic, total_frame_per_frame_labels

    #Load data into 2 lists: total_labels and frame_per_frame_labels
    def load_json(self,json_path):
        data = None
        with open(json_path) as json_file:
            data = json.load(json_file)

        if data is None:
            print "Cannot open json file with path: " +  json_path
            return None

        return data

    #Convert frames to videos(each video corresponds one label)
    def frames_2_videos(self,videos, videos_frame_per_frame_labels):
        processed = False
        
        new_videos = []
        label_videos = []
        for j in xrange(len(videos)):       
            frames = videos[j]        
            frame_per_frame_labels = videos_frame_per_frame_labels[j]
            i = 0
            initFrame = 0
            lastFrame = 0
            label = -2
            new_videos_from_video = []
            new_label_from_video = []
            #Save frames videos
            while(i < len(frames) and i < len(frame_per_frame_labels)):
                if label == -2:
                    label = frame_per_frame_labels[i]
                    initFrame = i
                else:
                    new_label = frame_per_frame_labels[i]
                    if label != new_label:
                        lastFrame = i-1
                        
                        new_videos_from_video.append(frames[initFrame:lastFrame])
                        new_label_from_video.append(label)
                        initFrame = i
                        label = new_label
                i+=1 
            new_videos.append(new_videos_from_video)
            label_videos.append(new_label_from_video)

        return new_videos, label_videos

    def process_videos(self, data_augmentation):
        self.videos, self.labels = data_augmentation.augmentate()
    #Folder with videos and txt containing labels (self.videos and self.labels)
    def output(self, PATH_VIDEOS):
        inverted_labels_dict = dict(map(reversed, self.labels_dic.items()))
        f = open(PATH_VIDEOS+"\labels.txt","w")
        for key in self.labels_dic.keys():
            id_value = self.labels_dic[key]
            f.write(key + " "+ str(id_value)+"\n")
        f.close()
        j=0
        #Output just one video in frames as testing
        for frame in self.videos[0]:
            cv2.imwrite(PATH_VIDEOS+"/frame"+str(j)+".png", frame)
            j+=1
        
        for i in xrange(len(self.videos)):
            video_name = inverted_labels_dict[self.labels[i]]
            height, width, layers = self.videos[i][0].shape
            size = (height, width)
            framerate = 60
            fourcc = cv2.VideoWriter_fourcc(*'DIVX')
            video = cv2.VideoWriter(PATH_VIDEOS+"/"+video_name + "_" +str(i)+".avi",fourcc,framerate,size)
            for j in range(len(self.videos[i])):                
                video.write(self.videos[i][j])
            video.release()

def main(images_path, json_path):
    preprocess = PreprocessVideos()
    videos, labels = preprocess.load_data(images_path, json_path)
    data_augmentation = VideoDataAugmentation(videos = videos, labels=labels)
    preprocess.process_videos(data_augmentation)
    dirName = "output"
    try:
        os.mkdir(dirName)
    except:
        pass
    preprocess.output(os.getcwd() + "\output")



if __name__ == "__main__":
    if len(sys.argv) <= 2:
        print "Not enough args: absolute_videos_folders_path absolute_json_folder_path"
        
    else:
        main(sys.argv[1], sys.argv[2])
