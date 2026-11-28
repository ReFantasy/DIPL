import numpy as np
import matplotlib.pyplot as plt
from matplotlib import image

# ---------- 1. 读入图像并转灰度 ----------
img = image.imread("/Users/refantasy/Code/DIPL/sample/data/DIP3E_Original_Images_CH04/Fig0429(a)(blown_ic).tif")          # 换成你的图片路径
if img.ndim == 3:
    img = img[..., :3].mean(axis=2)     # RGB -> 灰度
img = img.astype(np.float64)            # 统一转 float，便于运算

# ---------- 2. 二维 FFT ----------
F = np.fft.fft2(img)                    # 复数频谱，零频在左上角
Fshift = np.fft.fftshift(F)             # 零频移到中心，便于观察

# 幅度谱（对数变换，否则动态范围太大看不清）
mag = np.abs(Fshift)
mag_log = 20 * np.log10(mag + 1)

# 相位谱
phase = np.angle(Fshift)

# ---------- 3. 可视化 ----------
plt.figure(figsize=(12, 8))

plt.subplot(2, 2, 1)
plt.imshow(img, cmap='gray')
plt.title("Original Image")
plt.axis('off')

plt.subplot(2, 2, 2)
plt.imshow(mag_log, cmap='gray')
plt.title("Magnitude Spectrum (log, centered)")
plt.axis('off')

plt.subplot(2, 2, 3)
plt.imshow(phase, cmap='hsv')
plt.title("Phase Spectrum")
plt.axis('off')

# 未 fftshift 的原始幅度谱（零频在四角）
plt.subplot(2, 2, 4)
plt.imshow(20 * np.log10(np.abs(F) + 1), cmap='gray')
plt.title("Magnitude Spectrum (no shift)")
plt.axis('off')

plt.tight_layout()
plt.show()
