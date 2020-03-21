.PHONY: clean All

All:
	@echo "----------Building project:[ UOCinfectiousAgent - Debug ]----------"
	@cd "UOCinfectiousAgent" && "$(MAKE)" -f  "UOCinfectiousAgent.mk"
	@echo "----------Building project:[ UOCinfection - Debug ]----------"
	@cd "UOCinfection" && "$(MAKE)" -f  "UOCinfection.mk"
clean:
	@echo "----------Cleaning project:[ UOCinfectiousAgent - Debug ]----------"
	@cd "UOCinfectiousAgent" && "$(MAKE)" -f  "UOCinfectiousAgent.mk"  clean
	@echo "----------Cleaning project:[ UOCinfection - Debug ]----------"
	@cd "UOCinfection" && "$(MAKE)" -f  "UOCinfection.mk" clean
