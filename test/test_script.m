% Copyright (c) 2017-2018 Leo McCormack
%
% Permission is hereby granted, free of charge, to any person obtaining a copy
% of this software and associated documentation files (the "Software"), to deal
% in the Software without restriction, including without limitation the rights
% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
% copies of the Software, and to permit persons to whom the Software is
% furnished to do so, subject to the following conditions:
%
% The above copyright notice and this permission notice shall be included in
% all copies or substantial portions of the Software.
%
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
% OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
% THE SOFTWARE.

clear all, close all
dbstop if error
 
prefix = 'output/convhull_';
filenames = { 
    'airboat.m'
    'al.m'
    'ateneam.m'
    'cessna.m'
    'cube.m'
    'diamond.m'
    'dodecahedron.m'
    'gourd.m'
    'icosahedron.m'
    'lamp.m'
    'magnolia.m'
    'minicooper.m'
    'power_lines.m'
    'roi.m'
    'sandal.m'
    'shuttle.m'
    'skyscraper.m'
    'slot_machine.m'
    'symphysis.m'
    'tdesign_180_sph.m'
    'tdesign_840_sph.m'
    'tdesign_5100_sph.m'
    'teapot.m'
    'teddy.m'
    'trumpet.m'
    'venusm.m'
    'violin_case.m'};

for f=1:length(filenames)
    disp(['plotting:' filenames{f}])
    run(strcat(prefix, filenames{f}));
    vertices_hull = vertices + 0.0000001*randn(size(vertices));
    faces_ref = convhull(vertices_hull(:,1), vertices_hull(:,2), vertices_hull(:,3));
    
    % plot reference (matlab convhull function)
    figure
    subplot(1,2,1)
    for i=1:size(faces_ref,1) 
        plot3(vertices(faces_ref(i,:),1), vertices(faces_ref(i,:),2), vertices(faces_ref(i,:),3), 'k');
        hold on
        fill3(vertices(faces_ref(i,:),1), vertices(faces_ref(i,:),2), vertices(faces_ref(i,:),3),'b');
        hold on 
    end
    axis equal
    grid on
    xlabel('x'), ylabel('y'), zlabel('z')
    title(['MatLab ' num2str(size(faces_ref,1)) ' faces'])
    
    % plot convhull_3d
    subplot(1,2,2)
    for i=1:size(faces,1) 
        plot3(vertices(faces(i,:),1), vertices(faces(i,:),2), vertices(faces(i,:),3), 'k');
        hold on
        fill3(vertices(faces(i,:),1), vertices(faces(i,:),2), vertices(faces(i,:),3), 'b');
        hold on
    end
    axis equal
    grid on
    xlabel('x'), ylabel('y'), zlabel('z')
    title(['convhull\_3d ' num2str(size(faces,1)) ' faces'])
end

set(findall(gcf,'-property','FontSize'),'FontSize',14)

