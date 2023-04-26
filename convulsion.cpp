#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Funcion que define el filtro de convulsion
vector<vector<float>> convolve(vector<vector<float>> image, vector<vector<float>> kernel)
{
    int img_h = image.size();
    int img_w = image[0].size();
    int kernel_h = kernel.size();
    int kernel_w = kernel[0].size();
    int pad_h = kernel_h / 2;
    int pad_w = kernel_w / 2;
    
    vector<vector<float>> padded_img(img_h + 2 * pad_h, vector<float>(img_w + 2 * pad_w, 0));
    for (int i = pad_h; i < img_h + pad_h; i++) {
        for (int j = pad_w; j < img_w + pad_w; j++) {
            padded_img[i][j] = image[i - pad_h][j - pad_w];
        }
    }
    
    // GEnera el filtro de convulsion
    vector<vector<float>> result(img_h, vector<float>(img_w, 0));
    for (int i = pad_h; i < img_h + pad_h; i++) {
        for (int j = pad_w; j < img_w + pad_w; j++) {
            float sum = 0;
            for (int k = -pad_h; k <= pad_h; k++) {
                for (int l = -pad_w; l <= pad_w; l++) {
                    int x = i + k;
                    int y = j + l;
                    sum += kernel[k + pad_h][l + pad_w] * padded_img[x][y];
                }
            }
            result[i - pad_h][j - pad_w] = sum;
        }
    }
    
    return result;
}

int main()
{
    // Cargar imagen como un vector 2D de floats
    vector<vector<float>> img = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    // DEfinir el filtro como un vector 2D de floats
    vector<vector<float>> kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    
    vector<vector<float>> result = convolve(img, kernel);
    
    cout << "Original Image:" << endl;
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Filtered Image:" << endl;
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}

