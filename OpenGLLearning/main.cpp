//
//  main.cpp
//  OpenGLLearning
//
//  Created by konglee on 2019/10/5.
//  Copyright © 2019 konglee. All rights reserved.
//
#include "GLShaderManager.h"
#include "GLTools.h"
#include <GLUT/GLUT.h>
//#include<glut/glut.h>

/// 着色管理器
GLShaderManager shaderManager;

/// 批次处理工具
GLBatch batch;

// 窗口尺寸变化
void changeSize(int w, int h);

// 渲染屏幕
void renderScene();

// 创建
void setupRC();

int main(int argc, char *argv[]) {
    // 初始化 GLUT
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    
    // 注册回调函数
    glutReshapeFunc(changeSize);
    
    glutDisplayFunc(renderScene);
    
    GLenum err = glewInit();
    
    if (err != GLEW_OK) {
        printf("驱动程序初始化异常");
        return 1;
    }
    
    setupRC();
    
    glutMainLoop();
    return 0;
}

void setupRC() {
    
    // 设置背景颜色
    glClearColor(0.f, 0.f, 0.f, 1.f);
    
    // 初始化着色管理器
    shaderManager.InitializeStockShaders();
    
    // 设置顶点数组
    GLfloat vArrs[] = {
        0.f, 0.5f, 0.f,
        -0.5f, 0.f, 0.f,
        0.5f, 0.f, 0.f
    };
    
    // 三角形批次处理
    
    batch.Begin(GL_TRIANGLES, 3);
    batch.CopyVertexData3f(vArrs);
    batch.End();
}


void changeSize(int w, int h) {
    glViewport(0, 0, w, h);
}

void renderScene() {
 
    /// 清除一个或者特定的缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    GLfloat vRed[] = {1.f, 0.f, 0.f, 1.f};
    
    /// 传递到存储着色器，也就是 GLT_SHADER_IDENTITY 着色器, 这个着色器是以笛卡尔坐标系上渲染几何图形
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    
    /// 提交着色器
    batch.Draw();
    
    /// 后台缓冲区进行渲染，然后结束的时候交换到前台
    glutSwapBuffers();
    
}