import math
import copy
import random
import numpy as np
from PIL import Image, ImageDraw
from multiprocessing import Pool

class Painter():

    def __init__(self, N, input_file_name, output_file_name, T, N_children, max_obj_num):
        self.input_image = Image.open(input_file_name)
        self.input_data = np.asarray(self.input_image, dtype=np.int32)

        self.output_file_name = output_file_name

        self.w, self.h = self.input_image.size
        
        self.max_obj_num = max_obj_num

        self.img = Image.new("RGB", (self.w, self.h))
        self.drw = ImageDraw.Draw(self.img, 'RGBA')

        self.N = N
        self.N_children = N_children
        self.T = T

        self.fitness_history = []


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
        data = np.asarray(img, dtype=np.int32)
        #s = ssim(imageA, imageB)
        return np.sum((data - self.input_data)**2) / (data.shape[0] * data.shape[1])

    def mutate(self, indv, const):
        individual = copy.deepcopy(indv)
        for i,(cords,RGBA) in enumerate(individual):
            if i >= const:
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

        return individual

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

    def paint(self):
        # parameters
        obj_num = 5
        mutation_probability = 0.992

        population = self.get_random_population(obj_num,self.N)

        t = 0

        frames = [] # save GIF

        constant_obj = 0

        while t < self.T:
            new_obj_num = min(int(t/250)+3, self.max_obj_num)
            diff = new_obj_num - obj_num
            if diff > 0:
                for i,indv in enumerate(population):
                    population[i] += self.get_random_individual(diff)

                obj_num = new_obj_num
                constant_obj = obj_num - 2

            objective_values = [self.fitness(i) for i in population]

            population = [population[i] for i,_ in sorted(enumerate(objective_values), key=lambda x: x[1])]
            objective_values.sort()


            # frames to GIF
            if t%10 == 0:
                new_frame, drw = self.get_img_individual(population[0]) # best individual
                drw.text((0,0), 'iterations: {}\nfitness: {}\npolygons: {}'.format(t, objective_values[0], len(population[0])),  fill="white")
                frames.append(new_frame)

            old_population = copy.deepcopy(population)
            old_objective_values = copy.deepcopy(objective_values)

            population = []

            for i in range(self.N):
                for j in range(self.N_children):
                    if np.random.rand() <= mutation_probability:
                        population.append(self.mutate(old_population[i], constant_obj))
                    else:
                        population.append(self.get_random_individual(obj_num))

            objective_values = [self.fitness(i) for i in population]
            population = [population[i] for i,_ in sorted(enumerate(objective_values), key=lambda x: x[1])]
            objective_values.sort()

            objective_values.extend(old_objective_values)
            population.extend(old_population)

            population = [population[i] for i,_ in sorted(enumerate(objective_values), key=lambda x: x[1])]

            if t%100 == 0:
                print('\n{} iterations done\n{} fitness\n{} number of polygons\n'.format(t,min(self.fitness(population[0]),self.fitness(old_population[0])), len(population[0])))

            self.fitness_history.append(min(self.fitness(population[0]),self.fitness(old_population[0])))

            population = population[:self.N]

            t+=1

        new_frame, drw = self.get_img_individual(population[0]) # best individual
        new_frame.save(self.output_file_name + '.png',quality='keep')
        # Save into a GIF file
        frames[0].save(self.output_file_name+'.gif', format='GIF',
                       append_images=frames[1:], save_all=True, duration=4, loop=0)
