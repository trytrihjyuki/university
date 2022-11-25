import os
import json
import threading

from flask import Flask, request, flash, redirect, url_for, render_template

from utils import *
from main import start_process, init


UPLOAD_FOLDER = 'static/uploads/'

app = Flask(__name__)
app.secret_key = '1234'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
input_data = {}


@app.route('/', methods=['GET', 'POST'])
def upload_file():
    extension_info = request.args.get('extension_info')
    dimensions_info = request.args.get('dimensions_info')
    if request.method == 'POST':
        if 'watermark_file' not in request.files or 'photo_file' not in request.files:
            flash('No file part')
            return redirect(url_for('upload_file', extension_info=True)) # update website with information about avalible extensions
        watermark_file = request.files['watermark_file']
        photo_file = request.files['photo_file']
        watermark_ext = check_file(watermark_file)
        photo_ext = check_file(photo_file)

        # uploaded files had good extensions we can process further
        if watermark_ext is not None and photo_ext is not None:
            watermark_file.save(os.path.join(app.config['UPLOAD_FOLDER'], 'watermark.' + watermark_ext))
            photo_file.save(os.path.join(app.config['UPLOAD_FOLDER'], 'photo.' +  photo_ext))

            # save uploaded file extensions to config JSON
            with open('config.json', 'r+') as configs_f:
                configs = json.load(configs_f)
                configs['watermark_ext'] = watermark_ext
                configs['photo_ext'] = photo_ext
            set_configs(configs)
            try:
                resize_img() # we want to check img size and resize it to feasible for NN dimensions
            except ValueError:
                return redirect(url_for('upload_file', dimensions_info=True)) # We need to inform user that he needs to upload same sizes images
            return redirect(url_for('run'))
        else:
            return redirect(url_for('upload_file', extension_info=True))

    tags = {}
    if extension_info:
        tags['ext_instruction'] = True
    if dimensions_info:
        tags['dim_instruction'] = True
    return render_template('index.html', **tags)

@app.route('/run')
def run():
    configs = get_configs()
    return render_template('run.html', photo='photo.'+configs['photo_ext'], **configs)

@app.route('/run', methods=['POST'])
def get_params():
    configs = get_configs()
    configs['lr'] = float(request.form['lr'])
    configs['noise_reg'] = float(request.form['noise_reg'])
    configs['max_dim'] = int(request.form['max_dim'])
    configs['num_steps'] = int(request.form['num_steps'])
    configs['show_step'] = int(request.form['show_step'])
    set_configs(configs)
    clean(configs['max_dim'])
    # we can run the algorithm
    init()
    thread = threading.Thread(target=start_process)
    thread.daemon = True 
    thread.start()
    return redirect(url_for('live'))

@app.route('/live')
def live():
    configs = get_configs()
    run_info = get_run_info()
    if run_info['finished']:
        return redirect(url_for('finished'))
    return render_template('live.html', photo='photo.'+configs['photo_ext'], **run_info, **configs)

@app.route('/finished')
def finished():
    run_info = get_run_info()
    return render_template('finished.html', **run_info)

if __name__ == '__main__':
    app.debug = True
    app.config['SESSION_TYPE'] = 'filesystem'
    app.run()

