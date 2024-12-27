#include <glad/glad.h>
#include <SFML/Window.hpp>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

//定义几个有ndc坐标的三角形（为了方便），分别是X轴的左，右两侧，0，0.5的顶点，0，-0.5的顶点，共同组成一个平行四边形

float vertices1[] = {
        // positions         // colors
        0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
};

//索引
unsigned int indices1[] = {
        0, 1, 2, // first triangle
        0, 3, 2, // second triangle
};




//


int main() {

    // Window creation(以后可以封装在Window类中)
    sf::ContextSettings ctxSettings; // 创建OpenGL上下文设置
    ctxSettings.antialiasingLevel = 1; // 抗锯齿级别
    ctxSettings.depthBits = 24; // 深度缓冲区位数
    ctxSettings.majorVersion = 3; // 主版本号
    ctxSettings.minorVersion = 3; // 次版本号
    ctxSettings.stencilBits = 0; // 模板缓冲区位数
    ctxSettings.attributeFlags = ctxSettings.Core; // 属性标志
    // 创建一个窗口
    sf::Window window(sf::VideoMode({800, 600}), "OpenGL", sf::Style::Default, ctxSettings);


    // Load OpenGL functions using the glad library
    // 加载OpenGL函数 可以封装在Renderer类中

    if (!gladLoadGLLoader((GLADloadproc) sf::Context::getFunction)) {
        printf("Failed to initialize OpenGL context");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    //编译并链接 顶点和片段着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //检查编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //检查编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    //链接着色器
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //检查链接错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 配置VAO，VBO，EBO，批量初始化这些对象
    unsigned int VAO1, VBO1, EBO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO1);

    //配置VAO1的顶点数据和索引数据和指针
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    glBindVertexArray(0);//解绑VAO


    //渲染循环
while (window.isOpen()) {
        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Process events
        sf::Event event;

        //随机改变颜色
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            glClearColor((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
        } else {
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO1);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }




        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }



        // Clear the window


        // Draw OpenGL content here

        // Display the window
        window.display();
    }







    // Main loop

    return 0;
}