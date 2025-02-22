#include "../../src/svgdom/dom.hpp"
#include "../../src/svgdom/Visitor.hpp"
#include "../../src/svgdom/Cloner.hpp"

#include <utki/debug.hpp>

int main(int argc, char** argv){
	std::unique_ptr<svgdom::SvgElement> domOriginal = utki::makeUnique<svgdom::SvgElement>();
	
	std::unique_ptr<svgdom::PathElement> path = utki::makeUnique<svgdom::PathElement>();

	svgdom::PathElement::Step step;

	step.type = svgdom::PathElement::Step::Type_e::MOVE_ABS;
	step.x = 0;
	step.y = 0;
	path->path.push_back(step);

	step.type = svgdom::PathElement::Step::Type_e::LINE_ABS;
	step.x = 0;
	step.y = 300;
	path->path.push_back(step);

	step.type = svgdom::PathElement::Step::Type_e::LINE_ABS;
	step.x = 300;
	step.y = 300;
	path->path.push_back(step);

	step.type = svgdom::PathElement::Step::Type_e::LINE_ABS;
	step.x = 300;
	step.y = 0;
	path->path.push_back(step);

	domOriginal->children.push_back(std::move(path));

	svgdom::Cloner cloner;
	
	domOriginal->accept(cloner);
	
	std::unique_ptr<svgdom::SvgElement> domClone = cloner.getCloneAs<svgdom::SvgElement>();

	std::string domOriginalStr = domOriginal->toString();
	
	std::string domCloneStr = domClone->toString();
	
	ASSERT_ALWAYS(domOriginalStr == domCloneStr)
}
