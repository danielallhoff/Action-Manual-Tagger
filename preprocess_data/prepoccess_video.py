import json
import cv2
import numpy as np
import sys
import random
import os
class VideoDataAugmentation:
    def __init__(self, videos= None, labels = None, angle=15, scale=1.0, frames_variation_prob=0.2,frames_variation_add =2.0,brightness_variation=45, crop_pixels=20, trans_range = 5):
        self.angle = angle
        self.videos = videos
        self.video = videos[0]
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
        
    #Rotate frames of video
    def rotate(self):
        rotation = random.randint(0, self.angle)
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
        Trans_M = np.float32([[1,0,tr_x]])
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
            image = image[row_crop_pix:rows - row_crop_pix, cols_crop_pix:cols - cols_crop_pix]
            new_video.append(image)
        self.video = new_video
    
    #Add consecutive frames
    def duplicate_frames(self):
        label = self.labels[0]
        new_video = self.video
        new_labels = self.labels
        finished = False
        frames = [random.uniform(0,1) for _ in xrange(len(new_video))]
        
        i = 0
        while not finished:
            if frames[i] < frames_variation_prob:
                new_frames = random.randint(0, frames_variation_add)
                for frame in xrange(new_frames):
                    new_video.insert(i-1,self.new_video[i-1])
                    new_labels.insert(i-1, self.new_labels[i-1])
                    i+=1
            else:
                i+=1

            if(i >= len(self.new_video)):
                finished = True

        self.video = new_video
        self.labels = new_labels
        
    def change_brightness(self):
        new_video = []
        for image in self.video:
            hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
            cv2.add(hsv[:,:,2], value, hsv[:,:,2])
            image = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
            new_video.append(image)
        self.video = new_video
        pass
    def add_noise(self):
        new_video = []
        for image in self.video:
            gauss = np.random.normal(0,1, self.video[0].size)
            gauss = gauss.reshape(self.rows,self.cols,self.depth).astype('uint8')        
            image = cv2.add(image, gauss)
            new_video.append(image)
        self.video = new_video

    def add_blur(self):
        new_video = []
        for image in self.video:
            image = cv2.GaussianBlur(image, (5,5),0)
            new_video.append(image)
        self.video = new_video

    def augmentate(self, scale=5):
        total_videos = len(self.videos) * scale
        new_videos = []
        new_labels = []
        functions = [self.rotate, self.translate, self.flip_horizontal, self.crop, self.duplicate_frames, self.change_brightness,self.add_noise,self.add_blur]
        print len(self.videos)
        #Iterate the list of list of videos(each element are videos from same video and size)
        for i_video_list in xrange(len(self.videos)):
            
            self.cols = self.videos[i_video_list][0].shape[1]
            self.rows = self.videos[i_video_list][0].shape[0]
            self.depth = self.videos[i_video_list][0].shape[2]
            #Iterate all videos extracted from same video
            for i_video in xrange(len(self.videos[i_video_list])):
                print len(self.videos[i_video_list])
                for j in xrange(int(self.scale)):
                    self.video = self.videos[i_video_list][i_video]
                    
                    
                    random.shuffle(functions)
                    randnums = [random.uniform(0,1) for _ in xrange(len(functions))]
                    
                    for op in xrange(len(functions)):
                        if randnums[op] > 0.7:
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
            if(os.path.isdir(sub_dir_path)):
                images = []
                for filename in os.listdir(sub_dir_path):
                    
                    img = cv2.imread(os.path.join(sub_dir_path, filename))
                    if img is not None:
                        images.append(img)                        
                    else:
                        print "Cannot open image file with path: " + sub_dir_path+"/"+filename
                        return None
                json_data = self.load_json(json_folder_path+"/"+os.path.basename(sub_dir_path)+".json")
                if(json_data != None):                
                    self.videos.append(images)
                    json_videos_data.append(json_data)
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
                        
                        new_videos_from_video.extend(frames[initFrame:lastFrame])
                        new_label_from_video.append(label)
                        initFrame = i
                        label = new_label
                i+=1 
            new_videos.append(new_videos_from_video)
            label_videos.append(new_label_from_video)
        return new_videos, label_videos

    def process_videos(self, data_augmentation):
        self.videos, self.labels = data_augmentation.augmentate()
    #Folder with videos and txt containing labels
    #def output(self, PATH_VIDEOS):


def main(images_path, json_path):
    preprocess = PreprocessVideos()
    videos, labels = preprocess.load_data(images_path, json_path)
    data_augmentation = VideoDataAugmentation(videos = videos, labels=labels)
    preprocess.process_videos(data_augmentation)
    preprocess.output("/output")



if __name__ == "__main__":
    if len(sys.argv) <= 2:
        print "Not enough args: absolute_videos_folders_path absolute_json_folder_path"
        
    else:
        main(sys.argv[1], sys.argv[2])
