#pragma once
class Bindable {
public:
	virtual ~Bindable() = default;
	virtual void Bind() const = 0;
};