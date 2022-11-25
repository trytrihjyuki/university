import random
import time
import numpy as np
from torch import optim

from utils import *
from model.generator import *

INPUT_DEPTH = 32

def init():
    set_run_info({'loss': 0, 'step': 0, 'finished': False})

def start_process():
    configs = get_configs()
    watermark_ext = configs['watermark_ext']
    photo_ext = configs['photo_ext']
    MAX_DIM = configs['max_dim']
    NOISE_REG = configs['noise_reg']
    SHOW_STEP = configs['show_step']
    NUM_STEPS = configs['num_steps']
    DTYPE = torch.FloatTensor if configs['cuda'] == False else torch.cuda.FloatTensor

    # preprocess input photos
    watermark_pil, photo_pil = open_imgs(watermark_ext, photo_ext)
    watermark_np = pil_to_np(watermark_pil)
    photo_np = pil_to_np(photo_pil)
    watermark_var = np_to_tensor(watermark_np).type(DTYPE)
    photo_var = np_to_tensor(photo_np).type(DTYPE)

    # initializing model, optimizer, loss etc.
    generator = Generator(INPUT_DEPTH).type(DTYPE)
    mse = torch.nn.MSELoss().type(DTYPE)
    optimizer = optim.Adam(generator.parameters(), lr=configs['lr'])
    gen_input = generate_noise(INPUT_DEPTH, photo_pil.size[::-1], 'uniform').type(DTYPE)
    gen_input_og = gen_input.detach().clone()
    noise = gen_input.detach().clone()

    loss_values = []

    ANIMATION_STEP = max(NUM_STEPS // 200, 10)

    for i in range(NUM_STEPS + 1):
        print(i)
        optimizer.zero_grad()

        gen_input = gen_input_og + (noise.normal_() * NOISE_REG) # add noise regularization as in paper

        output = generator(gen_input)

        loss = mse(output * watermark_var, photo_var)
        loss.backward()
        loss_values.append(loss.item())

        # show current result
        if i%SHOW_STEP == 0:
            save_loss_plot(loss_values, MAX_DIM)
            print(loss.item())
            curr_pil = np_to_pil(tensor_to_np(output)[0])
            save_result(curr_pil)
            set_run_info({'loss': loss.item(), 'step': i, 'finished': False})

        if i%ANIMATION_STEP == 0:
            curr_pil = np_to_pil(tensor_to_np(output)[0])
            save_animation(curr_pil, i)

        optimizer.step()

    set_run_info({'loss': loss.item(), 'step': configs['num_steps'], 'finished': True})
    create_gif()
