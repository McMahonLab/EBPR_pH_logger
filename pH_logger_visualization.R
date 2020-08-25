library(tidyverse)
library(gridExtra)


#load data ----------------------------------------------------------------
pH_A <- read.table("PH_A.TXT", sep=",", header=F)
colnames(pH_A) <- c("Reactor","Datetime", "pH", "Voltage")

pH_B <- read.table("PH_B.TXT", sep=",", header=F)
colnames(pH_B) <- c("Reactor","Datetime", "pH", "Voltage")

pH_C <- read.table("PH_C.TXT", sep=",", header=F)
colnames(pH_C) <- c("Reactor","Datetime", "pH", "Voltage")


#plot ----------------------------------------------------------------------
#x1 <- pH_A %>% select("Datetime")
#x2 <- pH_B %>% select("Datetime")
#x3 <- pH_C %>% select("Datetime")
#y1 <- pH_A %>% select("pH")
#y2 <- pH_B %>% select("pH")
#y3 <- pH_C %>% select("pH")#TestCW

p1 <- ggplot(data = pH_A) + 
  geom_point(mapping = aes(x = Datetime, y = pH)) +
  labs(x = "Date and Time", y = "pH", title = "Reactor A") +
  theme(axis.text.x = element_text(angle = 60, hjust = 1)) 

p2 <- ggplot(data = pH_B) + 
  geom_point(mapping = aes(x = Datetime, y = pH)) +
  labs(x = "Date and Time", y = "pH", title = "Reactor B") +
  theme(axis.text.x = element_text(angle = 60, hjust = 1))

p3 <- ggplot(data = pH_C) + 
  geom_point(mapping = aes(x = Datetime, y = pH)) +
  labs(x = "Date and Time", y = "pH", title = "Reactor C") +
  theme(axis.text.x = element_text(angle = 60, hjust = 1))

grid.arrange(p1, p2, p3) #put days on top

ggplot(data = pH_A) + 
  geom_point(mapping = aes(x = Datetime, y = pH)) +
  labs(x = "Date and Time", y = "pH", title = "Reactor A") +
  theme(axis.text.x = element_text(angle = 60, hjust = 1))






