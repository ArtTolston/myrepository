#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
class Rectangle : public IShape {
	void SetPosition(Point p) override {
		position = p;
	}
	Point GetPosition() const override {
		return position;
	}
	void SetSize(Size s) override {
		size = s;
	}
	Size GetSize() const override {
		return size;
	}
	unique_ptr<IShape> Clone() const {
		unique_ptr<IShape> ptr = make_unique<Rectangle>();
		ptr->SetPosition(position);
		ptr->SetSize(size);
		ptr->SetTexture(texture);
		return ptr;
	}
	void SetTexture(shared_ptr<ITexture> t) override {
		texture = t;
	}
	ITexture* GetTexture() const override{
		return texture.get();
	}
	void Draw(Image& image) const override{
		int top_y = position.y, bottom_y = position.y + size.height - 1;
		int left_x = position.x, right_x = position.x + size.width - 1;
		Size image_sz;
		
		if (texture) {
			image_sz = texture->GetSize();
		}
		else {
			image_sz = { 0,0 };
		} 
		for (int y = top_y; y <= bottom_y; ++y) {
			for (int x = left_x; x <= right_x; ++x) {
				if (y - top_y < image_sz.height && x - left_x < image_sz.width) {
					image[y][x] = texture->GetImage().at(y - top_y).at(x - left_x);
				}
				else {
					image[y][x] = '.';
				}
			}
		}
		
	}
private:
	shared_ptr<ITexture> texture;
	Point position;
	Size size;
};

class Ellipse : public IShape {
	void SetPosition(Point p) override {
		position = p;
	}
	Point GetPosition() const override {
		return position;
	}
	void SetSize(Size s) override {
		size = s;
	}
	Size GetSize() const override {
		return size;
	}
	unique_ptr<IShape> Clone() const {
		unique_ptr<IShape> ptr = make_unique<Rectangle>();
		ptr->SetPosition(position);
		ptr->SetSize(size);
		ptr->SetTexture(texture);
		return ptr;
	}
	void SetTexture(shared_ptr<ITexture> t) override {
		texture = t;
	}
	ITexture* GetTexture() const override {
		return texture.get();
	}
	void Draw(Image& image) const override {
		int top_y = position.y, bottom_y = position.y + size.height - 1;
		int left_x = position.x, right_x = position.x + size.width - 1;

		Size image_sz;
		if (texture) {
			image_sz = texture->GetSize();
		}
		else {
			image_sz = { 0,0 };
		}	
		for (int y = top_y; y <= bottom_y; ++y) {
			for (int x = left_x; x <= right_x; ++x) {
				if (IsPointInEllipse({ x - left_x, y - top_y }, size)) {
					if (y - top_y < image_sz.height && x - left_x < image_sz.width) {
						image[y][x] = texture->GetImage().at(y - top_y).at(x - left_x);
					}
					else {
						image[y][x] = '.';
					}
				}
			}
		}

	}
private:
	shared_ptr<ITexture> texture;
	Point position;
	Size size;
};


// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	if (shape_type == ShapeType::Ellipse) {
		return make_unique<Ellipse>();
	}
	else {
		return make_unique<Rectangle>();
	}
}