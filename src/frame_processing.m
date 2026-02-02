function [MMSE, y] = frame_processing(x, N, oversamp)

if nargin < 3, oversamp=4; end % oversampling factor
if nargin < 2, N=256; end % num of FFT samples
lambda = 0.05; %param for noise calc
alpha = 20; %param for noise calc

bin_frames = 312;
frame_inc = N/oversamp; % =64
if mod(frame_inc,1) ~= 0, error('N/oversamp must be an integer frame_inc size.'); end
frame_inc = round(frame_inc);
overlap = N - frame_inc;
fs = 8000;
freq = (0:N/2-1)*fs/N;

f = (buffer(x, N, overlap, 'nodelay')).';
t = 0:(N-1);
w = sqrt((1-0.85185*cos((2*t+1)*pi/N))/oversamp); % Hamming window, 0.85 = 0.46/0.54

noisy_f_windowed = f .* w;
noisy_F = fft(noisy_f_windowed, N, 2); % along each frame (row)
mag = abs(noisy_F(:, 1:N/2));

% Section 3.3 Noise Estimation
% Initialize 4 MMSE bins
% NOTE: only half of spectrum needed because audio FT is symmetric
M1 = inf(1, N/2);
M2 = inf(1, N/2);
M3 = inf(1, N/2);
M4 = inf(1, N/2);
count_min = 0;

num_frames = size(f, 1);
for frame_idx = 1:num_frames
    mag_frame = mag(frame_idx,:);
    M1 = min(mag_frame, M1);
    count_min = count_min + 1;

    if count_min >= bin_frames
        count_min = 0;
        M4 = M3;
        M3 = M2;
        M2 = M1;
        M1 = mag_frame;
    end
end

MMSE = min([M1;M2;M3;M4], [], 1); % MINIMUM MEAN SPECTRAL ERROR
g = max(lambda, 1 - alpha * MMSE ./ (mag + eps));

f_clean = zeros(num_frames, N);

for frame_idx = 1:num_frames
    F_frame = noisy_F(frame_idx, :);
    F_enh = F_frame; %current frame for enhancement

    F_enh(1:N/2) = g(frame_idx, :) .* F_frame(1:N/2);
    F_enh(N/2+2:N) = conj(F_enh(N/2:-1:2)); % freq bins 130:256 == 128:-1:2
    f_clean(frame_idx,:) = real(ifft(F_enh,N));
end

f_clean_windowed = f_clean .* w; % apply windowing funct again

Lpad = (num_frames-1)*frame_inc + N;
y = zeros(1, Lpad); % Initialize output signal

for frame_idx = 1:num_frames
    idx = (frame_idx-1)*frame_inc+(1:N);
    y(idx) = y(idx) + f_clean_windowed(frame_idx,:);
end

y = y.';
% f_clean_windowed = y(1:length(f));

end