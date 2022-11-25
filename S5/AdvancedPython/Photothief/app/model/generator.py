import torch
from torch import nn

from .blocks import ConvBlock2d, Concat

class Generator(nn.Module):
    def __init__(self, input_channels, num_of_down_channels = 5*[128], num_of_up_channels = 5*[128], num_of_skip_channels = 5*[4]):
        super(Generator, self).__init__()

        network_depth = len(num_of_down_channels)

        # creating network structure
        self.model = nn.Sequential()
        main_model = self.model # main model (in current loop iteraion), we connect all deeper layers to this module every iteration

        for i in range(network_depth):

            deeper = nn.Sequential() # all of the deeper part of the network
            skip = nn.Sequential() # skip module, deeper+skip -> upper part of network

            if num_of_skip_channels[i] > 0:
                main_model.add_module('concat_'+str(i), Concat(1, skip, deeper))
            else:
                main_model.add_module('down_'+str(i), deeper)

            next_channels = num_of_up_channels[i + 1] if i < network_depth - 1 else num_of_down_channels[i]

            # batch norm on skip connection and upsample
            main_model.add_module('batchnorma_'+str(i), nn.BatchNorm2d(num_of_skip_channels[i] + next_channels))

            # convolution on skip connection
            if num_of_skip_channels[i]:
                skip.add_module('skipconv_'+str(i), ConvBlock2d(in_channels=input_channels, out_channels=num_of_skip_channels[i], stride=1, kernel_size=1))

            # convolution and downsample layers
            deeper.add_module('downsample_'+str(i), ConvBlock2d(in_channels=input_channels, out_channels=num_of_down_channels[i], stride=2, kernel_size=3))
            deeper.add_module('downconv_'+str(i), ConvBlock2d(in_channels=num_of_down_channels[i], out_channels=num_of_down_channels[i], stride=1, kernel_size=3))

            deeper_main = nn.Sequential() # all the i+1. i+2, ..., network_depth levels of U-shaped network that we create over the iteration of loop

            if i < network_depth: # we still go deeper
                deeper.add_module('deeperlvl_'+str(i), deeper_main)

            # upsample
            deeper.add_module('upsample_'+str(i), nn.Upsample(scale_factor=2, mode='nearest'))

            # convolution after during upsampling (after deepest point of network)
            main_model.add_module('upconv_'+str(i), ConvBlock2d(in_channels=num_of_skip_channels[i] + next_channels, out_channels=num_of_up_channels[i], stride=1, kernel_size=3))
            main_model.add_module('upconv1x1_'+str(i), ConvBlock2d(in_channels=num_of_up_channels[i], out_channels=num_of_up_channels[i], stride=1, kernel_size=1)) # optional recomended 1x1 conv

            input_channels = num_of_down_channels[i] # level lower, changing size of current input
            main_model = deeper_main # all deeper levels created over the iteration

        # last convolution layer and activation function
        self.model.add_module('upconv_'+str(network_depth), nn.Conv2d(in_channels=num_of_up_channels[0], out_channels=3, stride=1, kernel_size=1))
        self.model.add_module('sigmoid', nn.Sigmoid())

    def forward(self, x):
        return self.model(x)