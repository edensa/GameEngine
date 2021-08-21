import requests
import sys
import time
import click

from fake_useragent import UserAgent

def download_file(url, filepath):
    with open(filepath, 'wb') as f:
        ua = UserAgent()
        headers = {'User-Agent': ua.chrome}
        response = requests.get(url, headers=headers, stream=True)
        total = response.headers.get('content-length')

        if total is None:
            f.write(response.content)
        else:
            total = int(total)
            startTime = time.time()
            last_avg_update = startTime
            with click.progressbar(length=total, show_eta=True, show_percent=True) as bar: 
                for chunk in response.iter_content(chunk_size=1024):
                    if chunk:
                        f.write(chunk)
                        f.flush()                        
                        now = time.time()
                        if (now - last_avg_update) > 1:
                            last_avg_update = now
                            elapsedTime = now - startTime
                            avgKBPerSecond = (bar.pos / 1024) / elapsedTime
                            avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSecond)
                            if (avgKBPerSecond > 1024):
                                avgMBPerSecond = avgKBPerSecond / 1024
                                avgSpeedString = '{:.2f} MB/s'.format(avgMBPerSecond)
                            bar.label = avgSpeedString
                        bar.update(len(chunk))
    sys.stdout.write('\n')

def YesOrNo(default=None):
    return click.confirm("confirm?", default=default)
