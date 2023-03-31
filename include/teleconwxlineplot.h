#pragma once

#include "teleconwxplotxy.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

class TeleconWxLinePlot : public TeleconWxPlotXY, virtual public TeleconLinePlot {
public:
	TeleconWxLinePlot(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize);

	/* Functions inherited from TeleconLinePlot */
	int getLineWidth() const override;
	LineType getLineType() const override;
	bool hasSymbol() const override;
};
