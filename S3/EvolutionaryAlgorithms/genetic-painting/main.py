#!/usr/bin/python3
import argparse
from EvoPainting import Painter



def main():
    parser = argparse.ArgumentParser(description=f"GENETIC PAINTER {1.0}")

    parser.add_argument("image", type=str, help="Image to be processed")
    parser.add_argument("output", type=str, help="Name of output image")
    parser.add_argument("-N", "--population", help="Population size", type=int, default=1)
    parser.add_argument("-T", "--iterations", type=int, default=10000)
    parser.add_argument("-m", "--max-obj-num",help="Maximum number of triangles in the image", type=int, default=100)
    parser.add_argument("-c", "--number-children",help="Number of children of each individual", type=int, default=50)
    args = parser.parse_args()

    k = Painter(args.population, args.image, args.output, args.iterations, args.number_children, args.max_obj_num)
    k.paint()

if __name__ == "__main__":
    main()