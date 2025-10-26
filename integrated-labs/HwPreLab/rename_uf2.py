import os
import shutil
import datetime
import platform
import subprocess

Import('env')


clean_old_files = True
open_file_browser = True


def after_build(source, target, env):
    src_build_dir = env.subst('$BUILD_DIR')
    dst_build_dir = os.path.join(env.subst('$PROJECT_DIR'), 'build')
    original = os.path.join(src_build_dir, 'firmware.uf2')

    # If the source doesn't exist, there's nothing to be done
    if not os.path.exists(original):
        print('No firmware.uf2 generated; skipping copy.')
        return
    
    # If the destination doesn't exist, make it exist
    os.makedirs(dst_build_dir, exist_ok=True)

    # Timestamped filename
    # file_prefix = os.path.basename(env.subst('$PROJECT_DIR'))
    file_prefix = 'prelab8'
    timestamp = datetime.datetime.now().strftime('%Y%m%d-%H%M')
    filename = f'{file_prefix}-{timestamp}.uf2'

    # Paths
    target_in_src_build = os.path.join(src_build_dir, filename)
    target_in_dst_build = os.path.join(dst_build_dir, filename)

    # Clean up old files
    if clean_old_files:
        for f in os.listdir(src_build_dir):
            if f.endswith('.uf2') and f != 'firmware.uf2':
                os.remove(os.path.join(src_build_dir, f))
        for f in os.listdir(dst_build_dir):
            if f.endswith('.uf2') and f.startswith(file_prefix + '-'):
                os.remove(os.path.join(dst_build_dir, f))

    # Copy to both locations
    shutil.copy(original, target_in_src_build)
    shutil.copy(original, target_in_dst_build)

    print(f'Generated: {target_in_src_build}')
    print(f'Also copied to: {target_in_dst_build}')

    # Optionally open file explorer
    if open_file_browser:
        try:
            if platform.system() == 'Windows':
                subprocess.Popen(['explorer', dst_build_dir])
            elif platform.system() == 'Darwin':
                subprocess.Popen(['open', dst_build_dir])
            elif platform.system() == 'Linux':
                subprocess.Popen(['xdg-open', dst_build_dir])
            else:
                print('Auto-open not supported on this OS.')
        except Exception as e:
            print(f'Failed to open file explorer: {e}')

env.AddPostAction('buildprog', after_build)
