clc;
clear all;
close all;

% Fetch dust concentration data and timestamps from ThingSpeak
[parking1, Timestamps1] = thingSpeakRead(2531600, 'Fields', 1, 'NumPoints', 200);
[parking2, Timestamps2] = thingSpeakRead(2531600, 'Fields', 2, 'NumPoints', 200);
[parking3, Timestamps3] = thingSpeakRead(2531600, 'Fields', 3, 'NumPoints', 200);
[parking4, Timestamps4] = thingSpeakRead(2531600, 'Fields', 4, 'NumPoints', 200);
[parking5, Timestamps5] = thingSpeakRead(2531600, 'Fields', 5, 'NumPoints', 200);
[emergency, Timestamps6] = thingSpeakRead(2531600, 'Fields', 6, 'NumPoints', 200);
[total_profit, Timestamps7] = thingSpeakRead(2531600, 'Fields', 7, 'NumPoints', 200);
[total_cars_per_day, Timestamps8] = thingSpeakRead(2531600, 'Fields', 8, 'NumPoints', 200);

figure
% Plot the data
subplot(4,2,1)
stairs(Timestamps1, parking1);
% Label the axes and title the plot
ylabel('OFF - ON');
xlabel('Time');
title('parking1');
% Set the y-axis limits
ylim([-0.5, 1.5]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps1) - minutes(60*20), max(Timestamps1)]);
grid;

% Repeat the same steps for other subplots
% (subplots 2 to 8)

% Plot the data
subplot(4,2,2)
stairs(Timestamps2, parking2);
% Label the axes and title the plot
ylabel('OFF - ON');
xlabel('Time');
title('parking2');
% Set the y-axis limits
ylim([-0.5, 1.5]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps2) - minutes(60*20), max(Timestamps2)]);
grid;

% Repeat the same steps for other subplots
% (subplots 3 to 8)

% Plot the data
subplot(4,2,3)
stairs(Timestamps3, parking3);
% Label the axes and title the plot
ylabel('OFF - ON');
xlabel('Time');
title('parking3');
% Set the y-axis limits
ylim([-0.5, 1.5]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps3) - minutes(60*20), max(Timestamps3)]);
grid;

% Repeat the same steps for other subplots
% (subplots 4 to 8)

% Plot the data
subplot(4,2,4)
stairs(Timestamps4, parking4);
% Label the axes and title the plot
ylabel('OFF - ON');
xlabel('Time');
title('parking4');
% Set the y-axis limits
ylim([-0.5, 1.5]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps4) - minutes(60*20), max(Timestamps4)]);
grid;

% Repeat the same steps for other subplots
% (subplots 5 to 8)

% Plot the data
subplot(4,2,5)
stairs(Timestamps5, parking5);
% Label the axes and title the plot
ylabel('OFF - ON');
xlabel('Time');
title('parking5');
% Set the y-axis limits
ylim([-0.5, 1.5]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps5) - minutes(60*20), max(Timestamps5)]);
grid;

% Repeat the same steps for other subplots
% (subplots 6 to 8)

% Plot the data
subplot(4,2,6)
stairs(Timestamps6, emergency,'r');
% Label the axes and title the plot
ylabel('OFF - ON');
xlabel('Time');
title('EMERGENCY STATES');60*20
% Set the y-axis limits
ylim([-0.5, 1.5]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps6) - minutes(60*20), max(Timestamps6)]);
grid;

% Repeat the same steps for other subplots
% (subplots 7 to 8)

% Plot the data
subplot(4,2,7)
plot(Timestamps7, total_profit,'g');
% Label the axes and title the plot
ylabel('Egyption Pound LE');
xlabel('Time');
title('total profit');
% Set the y-axis limits
ylim([-0.5, 1000]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps7) - minutes(60*20), max(Timestamps7)]);
grid;

% Repeat the same steps for other subplots
% (subplot 8)

% Plot the data
subplot(4,2,8)
plot(Timestamps8, total_cars_per_day,'black');
% Label the axes and title the plot
ylabel('Number of cars');
xlabel('Time');
title('total cars ');
% Set the y-axis limits
ylim([-0.5, 200]);
% Limit x-axis to 2 days before the maximum timestamp
xlim([max(Timestamps8) - minutes(60*20), max(Timestamps8)]);
grid;


