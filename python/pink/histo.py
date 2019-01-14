# -*- coding: utf-8 -*-
#
# This software is licensed under 
# CeCILL FREE SOFTWARE LICENSE AGREEMENT

# This software comes in hope that it will be useful but 
# without any warranty to the extent permitted by applicable law.

# (C) M. Couprie <coupriem@esiee.fr>, 2011
# Université Paris-Est, Laboratoire d'Informatique Gaspard-Monge, Equipe A3SI, ESIEE Paris, 93162, Noisy le Grand CEDEX

# histograms 

from pink import python_component_missing # this is an exception class
import pink.windowing as wd

try:
    import numpy as np
except:
    print("error: could not import numpy, try to install python-numpy")
    raise python_component_missing

try:
    import matplotlib.pyplot as plt
except:
    print("error: could not import matplotlib, try to install python-numpy and python-matplotlib")
    raise python_component_missing

# ## Uncomment for debugging
# wd.options.debug=True

# histogram
def histogram(img,mask=None):
    if img.imtype() != 'uint8_t':
        print("histogram: error")
        return
    h = np.zeros(256)    
    N = img.size.prod()
    if mask == None:
        for i in range(N): h[img[i]] = h[img[i]] + 1
    else:
        for i in range(N):
            if mask[i] != 0: h[img[i]] = h[img[i]] + 1
    return h

# show histogram
def show_histo(img):
    h = histogram(img)
    x = np.array(range(256))
    y = np.zeros(256)
    fig = plt.figure()
    ax1 = fig.add_subplot(111)  # 1 row, 1 column, first (upper) plot
    ax1.vlines(x, y, h, lw=2)
    ax1.grid(True)
    ax1.axhline(0, color='black', lw=1)
    plt.show()
    return


# LuM end of file