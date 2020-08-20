library(tidyverse)

#load data ----------------------------------------------------------------
pH_A <- read.table("PH_A.TXT", sep=",", header=F)
colnames(pH_A) <- c("Reactor","Datetime", "pH", "Voltage")


#plot ----------------------------------------------------------------------
ggplot(data = pH_A) + 
  geom_point(mapping = aes(x = Datetime, y = pH))
