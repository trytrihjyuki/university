import math
import copy
import random
import numpy as np
from PIL import Image, ImageDraw
#from skimage.measure import structural_similarity as ssim

# GENETIC PAINTING

class Painter():

    def __init__(self, N, file_name, T, max_obj_num=25):
        self.input_image = Image.open(file_name)
        self.input_data = np.asarray(self.input_image)

        self.w, self.h = self.input_image.size
        
        self.max_obj_num = max_obj_num

        self.img = Image.new("RGB", (self.w, self.h))
        self.drw = ImageDraw.Draw(self.img, 'RGBA')

        self.N = N
        self.T = T


    def draw_object(self, cords, RGBA, drw):
        cords = list(map(tuple, cords))
        RGBA[3] = 120
        RGBA = tuple(RGBA)
        drw.polygon(cords,RGBA)

    def get_random_object(self):
        cords = np.random.randint(low=[0,0], high=[self.w,self.h], size=(3,2))
        RGBA = np.random.randint(256,size=4)
        return (cords, RGBA)

    def get_random_individual(self, obj_num):
        return [self.get_random_object() for _ in range(obj_num)]

    def get_random_population(self, obj_num, N):
        return [self.get_random_individual(obj_num) for _ in range(N)]

    def get_img_individual(self, individual):
        img = Image.new("RGB", (self.w, self.h))
        drw = ImageDraw.Draw(img, 'RGBA')
        # draw polygons
        for (c,rgb) in individual:
            self.draw_object(c, rgb, drw)

        return img, drw

    def fitness(self, individual):
        img, _ = self.get_img_individual(individual)

        # compute SSIM or MSE
        data = np.asarray(img)
        #s = ssim(imageA, imageB)
        return np.sum((data - self.input_data)**2) / (data.shape[0] * data.shape[1])

    def mutate(self, individual):
        for i,(cords,RGBA) in enumerate(individual):

            binary_vec = (np.random.random(3) < 1/3.).astype(int) # which cords we change
            cords[:,0] += (binary_vec * (self.w/6)*np.random.randn(3)).astype(int)
            cords[:,1] += (binary_vec * (self.h/6)*np.random.randn(3)).astype(int)


            binary_vec = (np.random.random(4) < 1/3.).astype(int) # which colors we change
            RGBA += binary_vec * (45 *np.random.randn(4)).astype(int)

            cords[:,0][cords[:,0] > self.w] = self.w
            cords[:,0][cords[:,0] < 0] = 0
            cords[:,1][cords[:,1] > self.h] = self.h
            cords[:,1][cords[:,1] < 0] = 0
            RGBA[RGBA > 255] = 255
            RGBA[RGBA < 0] = 0

            individual[i] = (cords,RGBA)

    def show_individual(self, individual):
        img, _ = self.get_img_individual(individual)
        img.show()

    def onep_crossover(self, p1, p2):
        p = np.random.randint(len(p1)-1) + 1
        return p1[:p] + p2[p:]

    def rand_crossover(self, p1, p2):
        tmp = p1+p2
        random.shuffle(tmp)
        return tmp[:len(p1)]

    def sort_f(self, x): # we need to sort to compare
        cords = x[0][0]
        return min(cords[0][1], cords[1][1], cords[2][1])

    def paint(self):
        # parameters
        obj_num = 5
        best_parents = int(self.N * 0.1)
        mutation_probability = 0.95
        x_prop = 0.92

        population = self.get_random_population(obj_num,self.N)

        t = 0

        frames = [] # save GIF

        while t < self.T:
            new_obj_num = min(int(t/400)+5, self.max_obj_num)
            diff = new_obj_num - obj_num
            if diff > 0:
                for i,indv in enumerate(population):
                    population[i] += self.get_random_individual(diff)
                obj_num = new_obj_num


            objective_values = [self.fitness(i) for i in population]
            population = [population[i] for i,_ in sorted(enumerate(objective_values), key=lambda x: x[1])]
            # sorted(population, key=self.sort_f)

            # frames to GIF
            new_frame, drw = self.get_img_individual(population[0]) # best individual
            drw.text((0,0), 'iterations: {}\nfitness: {}'.format(t, objective_values[0]),  fill="white")
            frames.append(new_frame)

            old_population = copy.deepcopy(population)

            if np.random.rand() < 0.92:
                offset = best_parents
            else:
                offset = 0

            # offset = 0

            for i in range(offset,self.N):
                if np.random.rand() < x_prop: # crossover
                    indices = np.random.choice(self.N, 2)
                    if np.random.rand() < 0.9:
                        population[i] = self.onep_crossover(old_population[indices[0]], old_population[indices[1]])
                    else:
                        population[i] = self.rand_crossover(old_population[indices[0]], old_population[indices[1]])
                else:                         # mutation
                    if np.random.rand() <= mutation_probability:
                        self.mutate(population[i])
                    else:
                        population[i] = self.get_random_individual(obj_num)

            if t%500 == 0:
                print('\n{} iterations done\n{} fitness\n{} number of polygons\n'.format(t,objective_values[0], len(population[0])))

            t+=1

        # Save into a GIF file
        frames[0].save('monalisa.gif', format='GIF',
                       append_images=frames[1:], save_all=True, duration=12, loop=0)
