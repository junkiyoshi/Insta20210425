#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float R = 300;
	int v_span = 10;
	int u_span = 10;

	for (int r = 30; r <= 100; r += 10) {

		for (int v = 0; v < 360; v += v_span) {

			auto noise_location = this->make_point(R, r * 3.5, 0, v);
			auto noise_value = ofNoise(glm::vec4(noise_location * 0.003, ofGetFrameNum() * 0.005));
			auto u_start = ofMap(noise_value, 0, 1, -360, 360);

			for (auto u = u_start; u < u_start + 60; u += u_span) {

				vector<glm::vec3> vertices;
				vertices.push_back(this->make_point(R, r, u, v - v_span * 0.5));
				vertices.push_back(this->make_point(R, r, u + u_span, v - v_span * 0.5));
				vertices.push_back(this->make_point(R, r, u + u_span, v + v_span * 0.5));
				vertices.push_back(this->make_point(R, r, u, v + v_span * 0.5));

				int index = face.getNumVertices();
				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); face.addIndex(index + 1); face.addIndex(index + 2);
				this->face.addIndex(index + 0); face.addIndex(index + 2); face.addIndex(index + 3);

				this->frame.addVertices(vertices);

				this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
				this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
				this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
				this->frame.addIndex(index + 3); this->frame.addIndex(index + 0);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(239);
	this->face.draw();

	ofSetColor(39);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}